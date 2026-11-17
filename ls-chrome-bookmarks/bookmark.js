const button = document.querySelector("#list");
const output = document.querySelector("#output");
const patternInput = document.querySelector("#pattern");

let showingResults = false;
button.addEventListener("click", async () => {
  if (showingResults) {
    output.replaceChildren();
    button.textContent = "List bookmarks";
    showingResults = false;
    return;
  }

  const pattern = patternInput.value.trim().toLowerCase();
  const tree = await chrome.bookmarks.getTree();

  // findMatches = (nodes) => {
  //   return nodes.flatMap(node => {
  //     const matches =
  //       node.url && (!pattern || node.url.toLowerCase().includes(pattern))
  //         ? [{ title: node.title, url: node.url }]
  //         : [];
  //     return [...matches, ...findMatches(node.children ?? [])];
  //   }
  // );

  let matches = [];
  findMatchesWithItsDir = (nodes, dirs = []) => {
    for (const node of nodes) {
      if (node.url) {
        if (!pattern || node.url.toLowerCase().includes(pattern)) {
          matches.push({
            title: node.title,
            url: node.url,
            parentPath: dirs.join(" / ") || "(root)"
          });
        }
      } else {
        const nextDirs = node.title ? [...dirs, node.title] : dirs;
        findMatchesWithItsDir(node.children ?? [], nextDirs);
      }
    }
  }
  findMatchesWithItsDir(tree);
  output.replaceChildren();

  for (const bookmark of matches) {
    const row = document.createElement("div");
    row.style.marginBottom = "10px";

    const parent = document.createElement("div");
    parent.textContent = `Folder: ${bookmark.parentPath}`;

    const link = document.createElement("a");
    link.href = bookmark.url;
    link.textContent = bookmark.title || bookmark.url;
    link.target = "_blank";
    link.rel = "noopener noreferrer";

    const url = document.createElement("div");
    url.textContent = bookmark.url;

    row.append(parent, link, url);
    output.append(row);
  }

  button.textContent = "Clear list";
  showingResults = true;
});
