import { readFileSync } from 'fs';

const buffer = () => {
    return readFileSync('./input.txt', 'utf8', (data) => {
        return data.toString();
    });
};

const parseFile = (file) => {
    return file
        .filter((x) => x !== '')
        .map((x) => {
            let nums = x.split(' ');
            for (let i = 0; i < nums.length; i++) {
                nums[i] = parseInt(nums[i]);
            }
            return nums;
        });
};

const calculate = (line) => {
    let end = false;
    let map = { 0: line };
    let x = line[0];
    let a = 1;
    while (!end) {
        let acc = [];
        let prevLine = map[a - 1];
        for (let i = 0; i < prevLine.length - 1; i++) {
            let diff = prevLine[i + 1] - prevLine[i];
            acc.push(diff);
        }
        map[a++] = acc;
        if (eol(acc)) {
            end = true;
        }
    }
    const values = Object.values(map);
    const next = [0];
    for (let i = values.length - 2; i >= 1; i--) {
        next.push(values[i][0] - next[next.length - 1]);
    }
    return x - next.pop();
};

const eol = (diff) => {
    for (let i = 0; i < diff.length; i++) {
        if (diff[i] !== 0) {
            return false;
        }
    }
    return true;
};

const main = () => {
    let ans = 0;
    let file = buffer()
        .split(/\r?\n/)
        .filter((x) => x !== x.length);

    let nums = parseFile(file);
    nums.forEach((line) => (ans += calculate(line)));
    console.log(ans);
};

main();
