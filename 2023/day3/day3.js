import { readFileSync } from 'fs';

let symbols = ['%', '=', '*', '#', '$', '@', '&', '/', '-', '+'];
let total = 0;
let len = 0;
let curNum = '';
const main = () => {
    let file = parse().split(/\r?\n/);
    for (let i = 0; i < file.length; i++) {
        for (let j = 0; j < file[i].length; j++) {
            let num = file[i][j];
            if (!isNaN(file[i][j])) {
                curNum += num;
                len++;
            }
            if (
                (len !== 0 && isNaN(file[i][j])) ||
                (len !== 0 && j === file[i].length - 1)
            ) {
                symbols.forEach((value) => {
                    let tick = 0;
                    if (
                        file[i][j] === value ||
                        file[i][j - len - 1] === value
                    ) {
                        total += parseInt(curNum);
                    }
                    while (tick <= len + 1) {
                        if (file[i + 1] && file[i + 1][j - tick] === value) {
                            total += parseInt(curNum);
                        } else if (
                            file[i - 1] &&
                            file[i - 1][j - tick] === value
                        ) {
                            total += parseInt(curNum);
                        }
                        tick++;
                    }
                });
                curNum = '';
                len = 0;
            }
        }
    }
    console.log(total);
};

// 534001 low

const parse = () => {
    return readFileSync('./input.txt', 'utf8', (data) => {
        return data.toString();
    });
};

main();
