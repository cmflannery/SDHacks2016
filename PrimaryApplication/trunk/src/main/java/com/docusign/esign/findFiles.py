import os

files = []

cwd = os.getcwd()
folders = ["api", "client", "model"]

for folder in folders:
    temp = []
    for file in os.listdir(os.path.join(cwd, folder)):
        if file.endswith(".java"):
            temp.append(file)
    output = []

    for entry in temp:
        output.append('import ' + entry)

    outputFile = os.path.join(cwd, folder) + '.java'
    openedFile = open(outputFile, 'w')
    for item in output:
        openedFile.write("%s\n" % item)

##thefile = open('.txt', 'w')
