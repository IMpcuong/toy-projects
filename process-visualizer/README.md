# Don't know what to introduce about this project yet!

- How to run:

```bash
cargo run
deno run --config ./tsconfig.json --allow-net ./src/chart/index.ts

deno compile --config ./tsconfig.json --allow-read --allow-write ./src/chart/index.ts
deno bundle --config ./tsconfig.json ./src/chart/index.ts ./src/chart/index.js
```