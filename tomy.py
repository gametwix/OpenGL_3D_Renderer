objFile = open("Statue.obj",'r')
objFile_my = open("Statue_my.obj",'w')
for line in objFile:
    split = line.split(' ')
    if split[0] == "v":
        objFile_my.write(line)
    if split[0] == "f":
        objFile_my.write('f')
        for num in split[1:]:
        
            num = num.split('/')[0]
            objFile_my.write(' ' + num)
        #objFile_my.write('\n')
objFile.close()
objFile_my.close()