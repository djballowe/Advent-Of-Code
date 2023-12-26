import { readFileSync } from 'fs';

const buffer = () => {
    return readFileSync('./input.txt', 'utf8', (data) => {
        return data.toString();
    });
};

const main = () => {
    const file = buffer()
        .split(/\r?\n/)
        .filter((x) => x !== x.length);
    const instructions = file.shift().split('');
    const nodes = parseNodes(file);
    const start = getStart(nodes);
    const steps = traverse(start, nodes, instructions);
    let ans = steps[0];
    steps.forEach((step) => {
       ans = lcm(ans, step) 
    })
    console.log(ans);
};

// 100 percent stolen I am not smart enough to come up with a recursive lowest common multiplyer function
const gdc = (a, b) => {
    return b === 0 ? a : gdc(b, a % b);
};

const lcm = (a, b) => {
    return (a * b) / gdc(a, b);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////

const traverse = (positions, nodes, instructions) => {
    let target = 'Z';
    return positions.map((start) => {
        let currentNode = start;
        let val = currentNode.val;
        let i = 0;
        let step = 0;
        while (val[2] !== target) {
            let pointer = instructions[i++ % instructions.length];
            let nextPointer = pointer === 'R' ? currentNode.R : currentNode.L;
            let next = nodes.find((x) => x.val === nextPointer);
            currentNode = next;
            val = next.val;
            step++;
        }
        return step;
    });
};

const getStart = (nodes) => {
    return nodes.filter((x) => x.val[2] === 'A');
};

const parseNodes = (file) => {
    const parse = file
        .filter((x) => x !== '')
        .map((node) => {
            let split = node.split('=');
            let val = split[0]
                .split('')
                .filter((x) => x !== ' ')
                .join('');
            let pointers = split[1].split(',').map((pointer) => {
                return pointer
                    .split('')
                    .filter(
                        (x) =>
                            (x.charCodeAt(0) >= 65 && x.charCodeAt(0) <= 90) ||
                            !isNaN(x)
                    )
                    .filter((x) => x !== ' ')
                    .join('');
            });
            return { val: val, L: pointers[0], R: pointers[1] };
        });
    return parse;
};

main();
