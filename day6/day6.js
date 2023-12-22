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
            parseInt(
                x
                    .split(':')[1]
                    .split(' ')
                    .filter((x) => x !== '')
                    .join('')
            )
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
        console.log(d)
    }
    return a.length;
};

const main = () => {
    const file = buffer();
    const data = parseTimes(file);

    let ans = 1;

    ans *= race(data.distance, data.time);

    console.log(ans);
};

main();
