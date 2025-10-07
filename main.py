def compression():
    data = input('enter your word: ')

    ptr = 0
    search_window = 10

    ans = []

    while ptr < len(data):
        i = max(0, ptr - search_window)
        j = ptr
        substring = ''
        prev_indx = -1
        count = 0

        print('==================begin===================')

        # searching algorithm
        while ptr < len(data):
            substring += data[ptr]
            indx = data.rfind(substring, i, j)

            print('ptr:', ptr)
            print('substring:', substring)
            print('i:', i)
            print('j:', j)
            print('indx:', indx)

            if indx == -1:
                break
            prev_indx = indx
            count += 1
            ptr += 1

        # If no match found at all
        if count == 0:
            ans.append([0, 0, data[ptr]])
            ptr += 1
        else:
            # The match failed one step after success
            length = len(substring) - 1
            offset = ptr - length - prev_indx

            # Handle last tag correctly (no next char at end)
            if ptr < len(data):
                next_char = data[ptr]
            else:
                next_char = ''  # no next char at end of data

            ans.append([offset, length, next_char])

            # Advance ptr: if we reached end, stop; otherwise move one step further
            if next_char == '':
                ptr = len(data)
            else:
                ptr += 1

        print('=================END==================')

    for i in ans:
        print(i)


def decompression():
    no_tags = int(input('enter the number of tags: '))

    myString = ''

    for i in range(no_tags):
        pos = int(input('enter the position: '))
        length = int(input('enter the length: '))
        symbol = input('enter the symbol: ')

        if pos == length and pos == 0:
            myString += symbol
        
        else:
            pos2 = len(myString)-pos
            print('pos2:',pos2)
            myString += myString[pos2:pos2+length]
            myString+=symbol

        print(myString)


decompression() 
    


        

