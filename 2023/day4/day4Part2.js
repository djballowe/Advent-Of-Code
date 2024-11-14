import { readFileSync } from 'fs';

let hash = new Map();
let total = 0;

const buffer = () => {
    return readFileSync('./input.txt', 'utf8', (data) => {
        return data.toString();
    });
};

const parse = (line) => {
    let trim = line.split(':')[1];
    let [win, val] = trim.split('|');
    return [
        win.split(' ').filter((x) => x !== ''),
        val.split(' ').filter((x) => x !== ''),
    ];
};

const main = () => {
    let file = buffer()
        .split(/\r?\n/)
        .filter((x) => x.length);
    let nums = file.map((line) => parse(line));
    let copies = new Array(nums.length).fill(1);
    let queue = 0;
    let matches = 0;
    while (queue < nums.length) {
        matches = load(nums[queue][0], nums[queue][1]);
        for (let i = queue + 1; i < queue + matches + 1; i++) {
            copies[i] += copies[queue];
        }
        queue++;
    }
    let sum = copies.reduce((acc, curr) => {
        return acc + curr;
    }, total);
    console.log(sum);
};

const load = (wins, vals) => {
    let matches = 0;
    wins.forEach((win) => hash.set(win, 0));
    vals.forEach((val) => {
        if (hash.has(val)) {
            hash.set(val, hash.get(val) + 1);
            matches += 1;
        }
    });
    hash.clear();
    return matches;
};

main();
