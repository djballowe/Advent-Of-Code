import { readFileSync } from 'fs';

const parseSeeds = (file) => {
    return file[0]
        .split(':')[1]
        .split(' ')
        .filter((x) => x !== '')
        .map((x) => parseInt(x));
};

const parseMaps = (file) => {
    let maps = [];
    let group = [];
    let isDigit = false;
    file.forEach((line) => {
        if (!isNaN(line[0])) {
            isDigit = true;
            group.push(line);
        } else if (isDigit && isNaN(line[0])) {
            isDigit = false;
            // this is cursed but fuck it
            maps.push(
                group.map((nums) => nums.split(' ').map((num) => parseInt(num)))
            );
            group = [];
        }
    });
    return maps;
};

const convert = (seeds, map) => {
    let ranges = map.map((set) => {
        return [set[1], set[1] + set[2], set[0] - set[1]];
    });
    for (let i = 0; i < seeds.length; i++) {
        for (let j = 0; j < ranges.length; j++) {
            if (seeds[i] >= ranges[j][0] && seeds[i] <= ranges[j][1]) {
                seeds[i] += ranges[j][2];
                break;
            }
        }
    }
    return seeds;
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
    let seeds = parseSeeds(file);
    let maps = parseMaps(file);
    maps.forEach((map) => {
        seeds = convert(seeds, map);
    })
    let ans = Math.min(...seeds)
    console.log(ans)
};

main();
