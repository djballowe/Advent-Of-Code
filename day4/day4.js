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
    let queue = 0;
    while (queue < nums.length) {
        load(nums[queue][0], nums[queue][1]);
        queue++;
    }
    console.log(total)
};

const load = (wins, vals) => {
    let points = 0;
    wins.forEach((win) => hash.set(win, 0));
    vals.forEach((val) => {
        if (hash.has(val)) {
            hash.set(val, hash.get(val) + 1)
            points = points === 0 ? points += 1 : points *= 2
        }
    })
    total += points;
    hash.clear()
    };

main();
