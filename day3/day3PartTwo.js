import { readFileSync } from 'fs';

const main = () => {
    let file = parse().split(/\r?\n/);
    for (let i = 0; i < file.length; i++) {
        for (let j = 0; j < file[i].length; j++) {
            let num = file[i][j];
            // if (!isNaN(file[i][j])) {
            //    curNum += num;
            //   len++;
            //}
            if (file[i][j] === '*') {
                let len = 2;
                let position = 0;
                let adjacent = new Set();
                let top = isNum(file[i - 1][j - (position - 1)]);
                let bottom = isNum(file[i + 1][j - (position - 1)]);
                let right = isNum(file[i][j + 1]);
                let left = isNum(file[i][j - 1]);
                while (position <= len && adjacent.size < 2) {
                    if (file[i - 1] && top) {
                        let num = getNum(file, -1, position, j, i);
                        adjacent.add(num);
                    }
                    if (file[i + 1] && bottom) {
                        let num = getNum(file, 1, position, j, i);
                        adjacent.add(num);
                    }
                    if (right) {
                        let num = getNum(file, 0, 0, j, i);
                        adjacent.add(num);
                    } else if (left) {
                        let num = getNum(file, 0, 2, j, i);
                        adjacent.add(num);
                    }
                    position++;
                }
                console.log(adjacent)
                adjacent.clear();
                position = 0;
            }
        }
    }
};

const parse = () => {
    return readFileSync('./test.txt', 'utf8', (data) => {
        return data.toString();
    });
};

const isNum = (num) => {
    return !isNaN(parseInt(num));
};

const getNum = (file, orientation, position, j, i) => {
    let counter = position;
    let num = '';
    while (isNum(file[i + orientation][j - (counter - 1)])) {
        counter++;
    }
    let start = j - (counter - 1) + 1;
    while (isNum(file[i + orientation][start])) {
        num += file[i + orientation][start];
        start++;
    }
    return parseInt(num);
};

main();
