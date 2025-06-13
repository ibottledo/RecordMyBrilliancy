from PIL import Image, ImageDraw, ImageFont
import sys
import os

square_size = 60
font_size = 48

# 유니코드 기물 매핑
unicode_pieces = {
    'K': '♔', 'Q': '♕', 'R': '♖', 'B': '♗', 'N': '♘', 'P': '♙',
    'k': '♚', 'q': '♛', 'r': '♜', 'b': '♝', 'n': '♞', 'p': '♟',
    '.': ' '
}

def get_font():
    # Mac용
    mac_font = "/System/Library/Fonts/Apple Symbols.ttf"
    # Ubuntu용
    linux_font = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"

    if os.path.exists(mac_font):
        return ImageFont.truetype(mac_font, font_size)
    elif os.path.exists(linux_font):
        return ImageFont.truetype(linux_font, font_size)
    else:
        return ImageFont.load_default()

def txt_to_chessboard(input_path, output_path):
    with open(input_path, 'r') as f:
        board = [line.strip().split() for line in f.readlines()]

    image_size = square_size * 8
    image = Image.new('RGB', (image_size, image_size), 'white')
    draw = ImageDraw.Draw(image)
    font = get_font()

    for y in range(8):
        for x in range(8):
            top_left = (x * square_size, y * square_size)
            bottom_right = ((x + 1) * square_size, (y + 1) * square_size)

            fill = "#739552" if (x + y) % 2 == 0 else "#EAEBD0"
            draw.rectangle([top_left, bottom_right], fill=fill)

            piece = board[y][x]
            symbol = unicode_pieces.get(piece, piece)

            bbox = draw.textbbox((0, 0), symbol, font=font)
            w = bbox[2] - bbox[0]
            h = bbox[3] - bbox[1]
            text_x = top_left[0] + (square_size - w) / 2
            text_y = top_left[1] + (square_size - h) / 2 - 5
            draw.text((text_x, text_y), symbol, font=font, fill='black')

    image.save(output_path)
    print(f"Saved chessboard image to: {output_path}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python txt_to_png.py input.txt output.png")
    else:
        txt_to_chessboard(sys.argv[1], sys.argv[2])
