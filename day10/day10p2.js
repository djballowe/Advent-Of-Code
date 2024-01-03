import { readFileSync } from 'fs';

const cords = [
    [-1, 0], // up
    [0, 1], // right
    [0, -1], // left
    [1, 0], // down
];

const directionMap = {
    0: [
        { val: '|', move: [-1, 0] },
        { val: 'F', move: [0, 1] },
        { val: '7', move: [0, -1] },
    ],
    1: [
        { val: '-', move: [0, 1] },
        { val: 'J', move: [-1, 0] },
        { val: '7', move: [1, 0] },
    ],
    2: [
        { val: '-', move: [0, -1] },
        { val: 'L', move: [-1, 0] },
        { val: 'F', move: [1, 0] },
    ],
    3: [
        { val: '|', move: [1, 0] },
        { val: 'L', move: [0, 1] },
        { val: 'J', move: [0, -1] },
    ],
};

const pathNodes = (file, i, j) => {
    return cords
        .map((cord) => {
            return {
                val: file[i + cord[0]][j + cord[1]],
                index: [i + cord[0], j + cord[1]],
                start: [i, j],
            };
        })
        .filter((node, d) => {
            let keys = directionMap[d];
            for (let e = 0; e < keys.length; e++) {
                if (keys[e].val === node.val) return node;
            }
        });
};

const findPaths = (file) => {
    for (let i = 0; i < file.length; i++) {
        for (let j = 0; j < file[i].length; j++) {
            if (file[i][j] === 'S') {
                return pathNodes(file, i, j);
            }
        }
    }
    return -1;
};

const getDirection = (direction) => {
    let index = -1;
    for (let i = 0; i < cords.length; i++) {
        if (cords[i][0] === direction[0] && cords[i][1] === direction[1]) {
            index = i;
        }
    }
    return index;
};

const traverse = (file, path) => {
    let prevNode = path.start;
    console.log(path);
    let step = 1;
    while (path.val !== 'S') {
        const direction = getDirection([
            path.index[0] - prevNode[0],
            path.index[1] - prevNode[1],
        ]);

        let value = path.val;
        directionMap[direction].forEach((x) => {
            if (x.val === value) {
                prevNode = path.index;
                file[path.index[0]][path.index[1]] = '+';
                path.index = path.index.map(
                    (indices, i) => (indices += x.move[i])
                );
                path.val = file[path.index[0]][path.index[1]];
            }
        });
        step++;
    }
    return step;
};

const buffer = () => {
    return readFileSync('./test.txt', 'utf8', (data) => {
        return data.toString();
    });
};

const main = () => {
    let file = buffer()
        .split(/\r?\n/)
        .filter((x) => x.length)
    const path = findPaths(file);

    let ans = traverse(file, path[0]);
    console.log(ans);
};

main();
