// Node.js 환경에서 실행되는 서버리스 함수입니다.
module.exports = async (req, res) => {
  // POST 요청만 허용합니다.
  if (req.method !== 'POST') {
    return res.status(405).json({ message: 'Method Not Allowed' });
  }

  const { url } = req.body;

  // 요청 본문에 URL이 있는지 확인합니다.
  if (!url) {
    return res.status(400).json({ message: 'URL is required' });
  }

  // 환경 변수에서 GitHub 토큰을 가져옵니다.
  const githubToken = process.env.GITHUB_PAT;
  if (!githubToken) {
    return res.status(500).json({ message: 'Server configuration error: GitHub token not set.' });
  }

  const owner = 'ibottledo';
  const repo = 'RecordMyBrilliancy';
  const workflow_id = 'add_move.yml'; // 1단계에서 만든 워크플로우 파일 이름

  try {
    // GitHub Actions 워크플로우를 트리거하는 API를 호출합니다.
    const response = await fetch(`https://api.github.com/repos/${owner}/${repo}/actions/workflows/${workflow_id}/dispatches`, {
      method: 'POST',
      headers: {
        'Authorization': `token ${githubToken}`,
        'Accept': 'application/vnd.github.v3+json',
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({
        ref: 'main', // 또는 주 브랜치 이름 (e.g., master)
        inputs: {
          url: url, // 워크플로우에 전달할 URL
        },
      }),
    });

    // GitHub API 호출 결과에 따라 응답을 보냅니다.
    if (response.status === 204) {
      res.status(202).json({ message: 'Request accepted. The brilliant move is being processed.' });
    } else {
      const errorText = await response.text();
      res.status(response.status).json({ message: `Error calling GitHub API: ${errorText}` });
    }
  } catch (error) {
    res.status(500).json({ message: `Internal Server Error: ${error.message}` });
  }
};
