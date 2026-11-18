const listButton = document.querySelector("#list");
const sortButton = document.querySelector("#sort");
const output = document.querySelector("#output");
const patternInput = document.querySelector("#pattern");

let showingResults = false;
let newestFirst = false;
let matches = [];

function renderMatches(matchedBookmarks) {
  const sortedMatches = [...matchedBookmarks].sort((f, s) =>
    newestFirst
      ? Number(s.dateAdded) - Number(f.dateAdded)
      : Number(f.dateAdded) - Number(s.dateAdded)
  );

  output.replaceChildren();

  for (const bookmark of sortedMatches) {
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

    const date = new Date(bookmark.dateAdded);
    const day = String(date.getDate()).padStart(2, "0");
    const month = String(date.getMonth() + 1).padStart(2, "0");
    const year = date.getFullYear();
    const added = document.createElement("div");
    added.textContent = `Added: ${day}-${month}-${year}`;

    row.append(parent, link, url, added);
    output.append(row);
  }
}

listButton.addEventListener("click", async () => {
  if (showingResults) {
    output.replaceChildren();
    listButton.textContent = "List bookmarks";
    showingResults = false;
    matches = [];
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

  matches = [];
  const findMatchesWithTheirDirs = (nodes, dirs = []) => {
    for (const node of nodes) {
      if (node.url) {
        if (!pattern || node.url.toLowerCase().includes(pattern)) {
          matches.push({
            title: node.title,
            url: node.url,
            parentPath: dirs.join(" / ") || "(root)",
            dateAdded: node.dateAdded ?? 0
          });
        }
      } else {
        const nextDirs = node.title ? [...dirs, node.title] : dirs;
        findMatchesWithTheirDirs(node.children ?? [], nextDirs);
      }
    }
  };
  findMatchesWithTheirDirs(tree);

  renderMatches(matches);
  listButton.textContent = "Clear list";
  showingResults = true;
});

sortButton.addEventListener("click", (event) => {
  event.preventDefault();

  if (!showingResults || matches.length == 0)
    return;

  newestFirst = !newestFirst;
  sortButton.textContent = newestFirst ? "Newest first" : "Oldest first";
  renderMatches(matches);
});
