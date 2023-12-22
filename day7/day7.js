import { readFileSync } from 'fs';


const buffer = () => {
    return readFileSync('./test.txt', 'utf8', (data) => {
        return data.toString();
    });
};

const parseCards = (file) => {
   let data = file.split(/\r?\n/).filter((x) => x.length).map((x) => {
        let parse = x.split(' ')
        let cards = parse[0].split('')
        let bid = parseInt(parse[1])
        return { hand: cards, bid: bid }
    });
   return data
};

const play = (hand, bid) => {
    let track = {}; 
    hand.forEach((card) => {
        track[card] ? track[card] += 1 : track[card] = 1
    })
    let num = new Array(5).fill(0)
    for (let key in track) {
        console.log(track[key])
        num[track[key] - 1]++
    }
    console.log(num)
}

const main = () => {
    const file = buffer();
    let cards = parseCards(file);
    play(cards[0].hand, cards[0].bid)
};

main();

// possible hands
// 1, 1, 1, 1, 1
// 1, 2, 1, 1 
// 1, 2, 2
// 3, 1, 1
// 2, 3 
// 1, 4
// 5 
