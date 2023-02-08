// NOTE: Uncomment all the script-tagged lines and convert to .html extension to run this script on your browser.
// <!-- <script src="https://cdnjs.cloudflare.com/ajax/libs/bowser/2.11.0/bundled.js"></script> -->
// <!-- <script> -->
// Source: https://code-boxx.com/detect-browser-with-javascript/

/**
 *  @type {Map<String, String>}
 */
const browserMap = new Map([
  ["Chrome0", "Google Chrome"],
  ["Chrome1", "Google Chrome"],
  ["Chrome2", "Google Chrome"],
  ["Chrome3", "Google Chrome"],
]);

browserMap.set("Chrome", "Google Chrome");
browserMap.set("Firefox", "Mozilla Firefox");
browserMap.set("MSIE", "Internet Explorer");
browserMap.set("Edge", "Internet Explorer");
browserMap.set("Safari", "Safari");
browserMap.set("Opera", "Opera");
browserMap.set("YaBrowser", "YaBrowser");

const mapIter = browserMap[Symbol.iterator]();
for (const item of mapIter) {
  console.log("Map iterator: ", item);
}

// NOTE: `typeof Map.entries()` == `iterator`.
//    Convert from `iterator` to `array` := `[...<iteratorObject>]`.
const sortedMap = new Map([...browserMap.entries()].sort((prev, next) => prev[0].length - next[0].length > 0));
sortedMap.forEach((k, v) => console.log("Sorted: ", k, v));

// FIXME: Wrong answer only!
console.log(navigator.userAgent);
window.addEventListener("load", () => {
  browserMap.forEach((k, v) => {
    navigator.userAgent.indexOf(k) != -1 ? console.log(v) : console.log("Nope!");
  });
});

// NOTE: Ordering is matter when detects user's browser.
window.addEventListener("load", () => {
  if (navigator.userAgent.indexOf("Chrome") != -1 ) {
    console.log("Google Chrome");
  } else if (navigator.userAgent.indexOf("Firefox") != -1 ) {
    console.log("Mozilla Firefox");
  } else if (navigator.userAgent.indexOf("MSIE") != -1 ) {
    console.log("Internet Explorer");
  } else if (navigator.userAgent.indexOf("Edge") != -1 ) {
    console.log("Internet Explorer");
  } else if (navigator.userAgent.indexOf("Safari") != -1 ) {
    console.log("Safari");
  } else if (navigator.userAgent.indexOf("Opera") != -1 ) {
    console.log("Opera");
  } else if (navigator.userAgent.indexOf("YaBrowser") != -1 ) {
    console.log("YaBrowser");
  } else {
    console.log("Others");
  }
});
// <!-- </script> -->