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
    let seedRanges = [];
    for (let i = 0; i < seeds.length; i += 2) {
        let ceil = seeds[i] + seeds[i + 1];
        let floor = seeds[i];
        let curSeed = seeds[i];
        let prevSeed = curSeed - 1;
        let count = seeds[i];
        for (let j = 0; j < ranges.length; j++) {
            while (count <= ceil) {
                let inRange = count >= ranges[j][0] && count <= ranges[j][1];
                if (inRange) {
                    curSeed = count + ranges[j][2];
                    if (curSeed < floor) {
                        floor = curSeed;
                    }
                } else {
                    curSeed = count;
                }
                if (prevSeed + 1 !== curSeed) {
                    seedRanges.push(floor, prevSeed);
                    floor = curSeed;
                }
                prevSeed = curSeed;
                count++;
            }
        }
    }
    return seedRanges;
};

const buffer = () => {
    return readFileSync('./test.txt', 'utf8', (data) => {
        return data.toString();
    });
};

const main = () => {
    let file = buffer()
        .split(/\r?\n/)
        .filter((x) => x.length);
    let seeds = parseSeeds(file);
    let maps = parseMaps(file);
    let ranges;
    maps.forEach((map) => {
        ranges = convert(seeds, map);
        console.log(ranges)
    });
    let ans = Math.min(...ranges);
    console.log(ans);
};

main();
