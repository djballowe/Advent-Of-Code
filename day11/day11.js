import { readFileSync } from 'fs';

const galaxy = '#';

const buffer = () => {
    return readFileSync('./input.txt', 'utf8', (data) => {
        return data.toString();
    });
};

const expand = (file) => {
    let rows = [];
    // expand rows
    for (let i = 0; i < file.length; i++) {
        let empty = true;
        for (let j = 0; j < file[i].length; j++) {
            if (file[i][j] === galaxy) {
                empty = false;
            }
        }
        if (empty) {
            rows.push(file[i]);
        }
        rows.push(file[i]);
    }
    // expand cols
    let i = 0;
    let j = 0;
    let empty = true;
    let cols = [];
    while (j < rows[0].length) {
        if (rows[i][j] === galaxy) {
            empty = false;
        }
        if (i++ === rows.length - 1) {
            if (empty) {
                cols.push(j);
            }
            i = 0;
            j++;
            empty = true;
        }
    }
    let space = [];
    for (let i = 0; i < rows.length; i++) {
        let newRow = [];
        for (let j = 0; j < rows[i].length; j++) {
            cols.forEach((col) => {
                if (j === col) {
                    newRow.push('.')
                }
            })
            newRow.push(rows[i][j])
        }
        space.push(newRow.join(''))
    }
    for (let i = 0; i < space.length; i++) {
        console.log(space[i]);
    }
    return space;
};

const getPairs = (space) => {
    let pairs = [];
    let points = [];
    for (let i = 0; i < space.length; i++) {
        for (let j = 0; j < space[i].length; j++) {
            if (space[i][j] === galaxy) {
                points.push([i, j]);
            }
        }
    }
    for (let i = 0; i < points.length; i++) {
        for (let j = i; j < points.length; j++) {
            if (
                points[i][0] === points[j][0] &&
                points[i][1] === points[j][1]
            ) {
                continue;
            } else {
                pairs.push([points[i], points[j]]);
            }
        }
    }
    return pairs;
};

const findPath = (pair, space) => {
    // BFS
    console.log(pair);
    let start = { node: pair[0], distance: 0 };
    let target = pair[1];
    let seen = new Set(`${start.node[0]},${start.node[1]}`);
    let queue = [start];

    while (queue.length) {
        let { node, distance } = queue.shift();

        if (node[0] === target[0] && node[1] === target[1]) {
            console.log(distance);
            return distance;
        }

        let nextNodes = [
            [node[0] + 1, node[1]],
            [node[0] - 1, node[1]],
            [node[0], node[1] + 1],
            [node[0], node[1] - 1],
        ];

        nextNodes.forEach((node) => {
            if (
                node[0] >= 0 &&
                node[0] < space.length &&
                node[1] >= 0 &&
                node[1] < space[0].length &&
                !seen.has(`${node[0]},${node[1]}`)
            ) {
                seen.add(`${node[0]},${node[1]}`);
                queue.push({ node: node, distance: distance + 1 });
            }
        });
    }
    throw new Error('No distance found')
};

const main = () => {
    let file = buffer()
        .split(/\r?\n/)
        .filter((x) => x.length)
    let space = expand(file);
    let pairs = getPairs(space);
    let ans = 0;
    pairs.forEach((pair) => (ans += findPath(pair, space)));
    console.log(ans)
};


main();
