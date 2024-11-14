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

const check = (index1, index2) => {
    return index1[0] === index2[0] && index1[1] === index2[1];
};

const traverse = (file, path1, path2) => {
    let prevNode1 = path1.start;
    let prevNode2 = path2.start;
    let intersect = false;
    let step = 1;
    while (!intersect) {
        const direction1 = getDirection([
            path1.index[0] - prevNode1[0],
            path1.index[1] - prevNode1[1],
        ]);
        const direction2 = getDirection([
            path2.index[0] - prevNode2[0],
            path2.index[1] - prevNode2[1],
        ]);
        let value = path1.val;
        let value2 = path2.val;
        directionMap[direction1].forEach((x) => {
            if (x.val === value) {
                prevNode1 = path1.index;
                path1.index = path1.index.map(
                    (indices, i) => (indices += x.move[i])
                );
                path1.val = file[path1.index[0]][path1.index[1]];
            }
        });
        directionMap[direction2].forEach((x) => {
            if (x.val === value2) {
                prevNode2 = path2.index;
                path2.index = path2.index.map(
                    (indices, i) => (indices += x.move[i])
                );
                path2.val = file[path2.index[0]][path2.index[1]];
            }
        });
        step++;
        intersect = check(path1.index, path2.index);
        console.log(path2);
    }
    return step
};

const buffer = () => {
    return readFileSync('./input.txt', 'utf8', (data) => {
        return data.toString();
    });
};

const main = () => {
    let file = buffer()
        .split(/\r?\n/)
        .filter((x) => x.length);
    const [path1, path2] = findPaths(file);

    let ans = traverse(file, path1, path2);
    console.log(ans)
};

main();
