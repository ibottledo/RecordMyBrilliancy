from PIL import Image, ImageDraw, ImageFont
import sys
import os
import io
import cairosvg # Added cairosvg

square_size = 60

# Piece asset path
PIECE_ASSET_PATH = "assets/pieces/"

# Mapping from FEN piece characters to their SVG filenames
# User specified: lt for light, dt for dark, k, q, r, b, n, p for piece types
# Example: Chess_klt45.svg for white King, Chess_qlt45.svg for black Queen
PIECE_FILENAME_MAP = {
    'K': 'Chess_klt45.svg', 'Q': 'Chess_qlt45.svg', 'R': 'Chess_rlt45.svg',
    'B': 'Chess_blt45.svg', 'N': 'Chess_nlt45.svg', 'P': 'Chess_plt45.svg',
    'k': 'Chess_kdt45.svg', 'q': 'Chess_qdt45.svg', 'r': 'Chess_rdt45.svg',
    'b': 'Chess_bdt45.svg', 'n': 'Chess_ndt45.svg', 'p': 'Chess_pdt45.svg',
}

# Dictionary to store loaded and converted piece images
loaded_piece_images = {}

def load_piece_images(size):
    """Loads SVG piece images, converts them to PNG, and resizes them."""
    for fen_char, filename in PIECE_FILENAME_MAP.items():
        svg_path = os.path.join(os.path.dirname(__file__), '..', PIECE_ASSET_PATH, filename)
        if not os.path.exists(svg_path):
            print(f"Error: Piece SVG file not found at {svg_path}")
            sys.exit(1)

        # Convert SVG to PNG bytes in memory
        png_bytes = cairosvg.svg2png(url=svg_path, output_width=size, output_height=size)
        
        # Open with Pillow
        piece_img = Image.open(io.BytesIO(png_bytes)).convert("RGBA")
        
        # Resize to square_size (cairosvg output_width/height should handle this, but good to be sure)
        piece_img = piece_img.resize((size, size), Image.Resampling.LANCZOS)
        loaded_piece_images[fen_char] = piece_img

def txt_to_chessboard(input_path, output_path):
    with open(input_path, 'r') as f:
        board_data = [line.strip().split() for line in f.readlines()]

    image_size = square_size * 8
    board_image = Image.new('RGB', (image_size, image_size), 'white')
    
    # Load piece images once
    if not loaded_piece_images: # Load only if not already loaded
        load_piece_images(square_size)

    for r in range(8):
        for c in range(8):
            top_left_x = c * square_size
            top_left_y = r * square_size
            
            fill_color = "#739552" if (r + c) % 2 == 1 else "#EAEBD0"
            ImageDraw.Draw(board_image).rectangle(
                [(top_left_x, top_left_y), (top_left_x + square_size, top_left_y + square_size)],
                fill=fill_color
            )

            piece_char = board_data[r][c]
            if piece_char != '.':
                piece_img = loaded_piece_images.get(piece_char)
                if piece_img:
                    # Paste piece image onto the board. Use piece_img as mask for transparency.
                    board_image.paste(piece_img, (top_left_x, top_left_y), piece_img)
                else:
                    print(f"Warning: No image found for piece '{piece_char}'")

    board_image.save(output_path)
    print(f"Saved chessboard image to: {output_path}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python txt_to_png.py input.txt output.png")
    else:
        txt_to_chessboard(sys.argv[1], sys.argv[2])