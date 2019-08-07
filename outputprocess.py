lines = []
result = []
with open ('output.txt', 'r') as in_file:
    for line in in_file:
        lines.append(line)
    sub = "description"
    res = "\n".join(s for s in lines if sub.lower() in s.lower())
    string = res[26:45]
    #print(string)
    for i in string:
        if i.isalpha() and i != 'n':
            result.append(i)
    print(''.join(result))
    
