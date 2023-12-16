import { readFileSync } from 'fs';

const main = () => {
    let file = buffer();
     
};

const buffer = () => {
    return readFileSync('./test.txt', 'utf8', (data) => {
        return data.toString();
    });
};

main();
