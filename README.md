# ♟ RecordMyBrilliancy
RecordMyBrilliancy is a tool designed for chess players to archive and showcase their Brilliant Moves from Chess.com.

[Live Demo](https://ibottledo.github.io/RecordMyBrilliancy/)

## Feature
- **Streak UI:** Visualizes your consistency with a built-in streak tracking system.
- **PNG Rendering:** Renders the chess board state just before the move into a PNG image.
- **Automated Posting:** Generates Markdown posts and publishes them to your GitHub Pages blog automatically.

## Setup for Your Own Brilliant Moves Blog

Follow these steps to fork this project and set up your personal recording blog.

### 1. Fork and Clone

First, Fork this repository to your GitHub account and Clone it to your local machine.

### 2. Run the Setup Script

Execute the `setup.sh` script in the root directory. This script will prompt you for your Chess.com username and GitHub details to automatically configure `config.json` and `_config.yml`.

```bash
chmod +x setup.sh
./setup.sh
```

### 3. GitHub Personal Access Token (PAT) Setting

To allow GitHub Actions to push changes to your repository, you need to set up a Personal Access Token.

**1.  Generate a PAT:** Go to GitHub `Settings` -> `Developer settings` -> `Personal access tokens` -> `Tokens (classic)` -> `Generate new token`
- Scope: Ensure you check the `repo` and `workflow` scopes.

**2.  Add Secret:** Go to your forked repository's `Settings` -> `Secrets and variables` -> `Actions` -> `New repository secret`
- Name: `GITHUB_PAT`
- Value: Paste your generated token here.

### 4. Deploy Vercel API & Environment Variables

The Vercel API acts as a bridge to trigger the recording process via a URL.

**1.  Deploy to Vercel:** Create a Vercel account and connect your GitHub repository to deploy the `api/add-move.js` file.

**2.  Set Environment Variables:** In your Vercel project settings, add the following variables:
- `GITHUB_PAT`: Your GitHub Personal Access Token.
- `GITHUB_OWNER`: Your GitHub username.
- `GITHUB_REPO`: Your repository name (e.g., `RecordMyBrilliancy`).
then deploy your Vercel project for the changes to take effect.

### 5. Activate GitHub Pages

To make your blog live: 

1.  Go to repository `Settings` -> `Pages`.
2.  Set `Source` to `Deploy from a branch`.
3.  Select the `gh-pages` branch (or `main`) and the `/(root)` folder.
4.  Save your settings. Your blog will be live at `https://<your-username>.github.io/<repo-name>/` in a few minutes.

## Languages Used
[![Languages](https://skillicons.dev/icons?i=cpp,python)](https://skillicons.dev)