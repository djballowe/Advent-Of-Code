import { readFileSync } from 'fs';

const buffer = () => {
    return readFileSync('./input.txt', 'utf8', (data) => {
        return data.toString();
    });
};

const parseTimes = (file) => {
    let data = file
        .split(/\r?\n/)
        .filter((x) => x.length)
        .map((x) =>
            x
                .split(':')[1]
                .split(' ')
                .filter((x) => x !== '')
        );
    return { time: data[0], distance: data[1] };
};

const race = (distance, time) => {
    let max = time - 1;
    let hold = max;
    let d;
    let a = [];
    while (hold) {
        let t = time - hold;
        d = t * hold;
        d > distance ? a.push(hold--) : hold--;
    }
    return a.length;
};

const main = () => {
    const file = buffer();
    const data = parseTimes(file);

    let ans = 1;

    for (let i = 0; i < data.distance.length; i++) {
        ans *= race(data.distance[i], data.time[i]);
    }

    console.log(ans);
};

main();
