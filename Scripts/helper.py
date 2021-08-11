# helper function to extract keywords     

def extractKeywords(string):
    string = string.replace("Hi-5", 'high five')
    string = string.replace("-", ' ')

    if string != '':
        print(string)
    diction = ['hello', 'high five', 'bye', 'hold', 'drop', 'recognize']
    comm =''
    
    for i in range(len(diction)):
        if diction[i] in string:
            
            comm = diction[i]
            break
    return comm

