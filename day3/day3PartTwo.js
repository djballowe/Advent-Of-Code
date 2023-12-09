import { readFileSync } from 'fs';

let total = 0;
let len = 0;
let curNum = '';
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
                let count = 0;
                let num = '';
                while (count <= len) {
                    if (file[i - 1] && !isNaN(file[i - 1][j - (count - 1)])) {
                        // while (!isNaN(file[i - 1][j - (count - 1)])) {
                           //  count++;
                        // }
                        console.log(file[i - 1][j - (count - 1)]);
                    }
                    curNum = '';
                    count++;
                }
                count = 0;
            }
        }
    }
};

// 534001 low

const parse = () => {
    return readFileSync('./test.txt', 'utf8', (data) => {
        return data.toString();
    });
};

main();
