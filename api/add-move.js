module.exports = async (req, res) => {
  // 1. CORS 허용 헤더 설정
  res.setHeader('Access-Control-Allow-Credentials', true);
  res.setHeader('Access-Control-Allow-Origin', '*'); // 특정 도메인만 허용하려면 'https://ibottledo.github.io' 를 입력하세요.
  res.setHeader('Access-Control-Allow-Methods', 'GET,OPTIONS,PATCH,DELETE,POST,PUT');
  res.setHeader('Access-Control-Allow-Headers', 'X-CSRF-Token, X-Requested-With, Accept, Accept-Version, Content-Length, Content-MD5, Content-Type, Date, X-Api-Version');

  // 2. 브라우저의 사전 요청(OPTIONS) 처리
  if (req.method === 'OPTIONS') {
    res.status(200).end();
    return;
  }

  // 3. POST 요청이 아닌 경우 차단
  if (req.method !== 'POST') {
    return res.status(405).json({ message: 'Method Not Allowed' });
  }

  const { url } = req.body;

  if (!url) {
    return res.status(400).json({ message: 'URL is required' });
  }

  const githubToken = process.env.GITHUB_PAT;
  if (!githubToken) {
    return res.status(500).json({ message: 'Server configuration error: GitHub token not set.' });
  }

  const owner = 'ibottledo';
  const repo = 'RecordMyBrilliancy';
  const workflow_id = 'add_move.yml';

  try {
    const response = await fetch(`https://api.github.com/repos/${owner}/${repo}/actions/workflows/${workflow_id}/dispatches`, {
      method: 'POST',
      headers: {
        'Authorization': `token ${githubToken}`,
        'Accept': 'application/vnd.github.v3+json',
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({
        ref: 'main',
        inputs: { url: url },
      }),
    });

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