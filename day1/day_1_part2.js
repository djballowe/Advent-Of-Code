import { readFileSync } from 'fs'

const dict = {
    one: 'on1e',
    two: 'tw2o',
    three: 'thr3ee',
    four: 'fou4r',
    five: 'fi5ve',
    six: 'si6x',
    seven: 'se7en',
    eight: 'ei8ght',
    nine: 'ni9ne',
}

const main = () => {
    let file = replace()
    let split = file.split(/\r?\n/)
    let reg = /(?:one|two|three|four|five|six|seven|eight|nine)/g
    let array = split.map((line) => {
        return line.replace(reg, (match) => {
            return dict[match]
        })
    })

    let actualArray = array.map((line) => {
        return line.replace(reg, (match) => {
            return dict[match]
        })
    })

    let f = ''
    let l = ''
    let total = 0

    console.log(actualArray)

    for (let i = 0; i < actualArray.length; i++) {
        for (let j = 0; j < actualArray[i].length; j++) {
            let ans = ''
            let c = actualArray[i][j]
            if (c >= '0' && c <= '9' && (f > '9' || f < '0')) {
                f = c
                l = c
            } else if (c >= '0' && c <= '9' && f >= '0' && f <= '9') {
                l = c
            }
            if (j === actualArray[i].length - 1) {
                if (l > '9' || l < '0') {
                    l = f
                }
                ans = f + l
                total += parseInt(ans)
                console.log(ans)
                f = ''
                l = ''
            }
        }
    }
    console.log(total)
}
// 53348
const replace = () => {
    return readFileSync('./inputs.txt', 'utf8', (data) => {
        return data.toString()
    })
}

main()
