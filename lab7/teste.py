import os

arqs = os.listdir()
for arq in arqs:
    if not arq.endswith("log"):
        arqs.remove(arq)

arqs.remove("bin")
for arq in arqs:
    i = 0  
    with open(arq) as f:
        for line in f:
            i += 1
    print("Numero de linhas no arquivo", arq, "=", i)
