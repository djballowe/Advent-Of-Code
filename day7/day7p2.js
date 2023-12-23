import { readFileSync } from 'fs';

const hands = {
    50000: 7,
    31000: 6,
    12000: 5,
    20100: 4,
    '01100': 3,
    10010: 2,
    '00001': 1,
};

const ranks = {
    A: 14,
    K: 13,
    Q: 12,
    J: 1,
    T: 10,
    9: 9,
    8: 8,
    7: 7,
    6: 6,
    5: 5,
    4: 4,
    3: 3,
    2: 2,
};

const joker = 'J';
let weLiveInASociety = false;

const buffer = () => {
    return readFileSync('./test.txt', 'utf8', (data) => {
        return data.toString();
    });
};

const parseCards = (file) => {
    let data = file
        .split(/\r?\n/)
        .filter((x) => x.length)
        .map((x) => {
            let parse = x.split(' ');
            let cards = parse[0].split('');
            let bid = parseInt(parse[1]);
            return { hand: cards, bid: bid };
        });
    return data;
};

const rankHand = (card) => {
    console.log('-----------------------')
    let track = {};
    card.hand.forEach((card) => {
        track[card] ? (track[card] += 1) : (track[card] = 1);
    });
    let freq = new Array(5).fill(0);
    let hp = -1;
    for (let key in track) {
        weLiveInASociety = key === joker ? true : false;
        freq[track[key] - 1]++;
        if (freq[track[key] - 1] > hp && !weLiveInASociety) {
           console.log(track[key] - 1)
            hp = track[key] - 1;
        }
    }
    if (track[joker]) {
        console.log(card);
        console.log(freq);
        console.log(hp)
        freq[track[joker] - 1]--;
        if (freq[track[joker]] !== freq[hp]) { // theres something wrong here
            freq[hp]--;
        }
        freq[hp + track[joker]]++;
        console.log(freq);
        console.log('-------------------');
    }
    card.rank = hands[freq.join('')];
};

const main = () => {
    const file = buffer();
    let cards = parseCards(file);
    let ans = 0;
    cards.forEach((card) => rankHand(card));
    cards.sort((a, b) => b.rank - a.rank);
    cards.sort((a, b) => {
        for (let i = 0; i < a.hand.length; i++) {
            if (a.rank === b.rank && a.hand[i] !== b.hand[i]) {
                return ranks[a.hand[i]] - ranks[b.hand[i]];
            }
        }
    });
    cards.forEach((card, i) => (ans += card.bid * (i + 1)));
    console.log(ans);
};

// 250207223 high
// 252489153 high

main();

// possible hands
// 1, 1, 1, 1, 1
// 1, 2, 1, 1
// 1, 2, 2
// 3, 1, 1
// 2, 3
// 1, 4
// 5
