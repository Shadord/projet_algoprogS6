import numpy as np
import matplotlib.pyplot as plt

myFile = open("save.txt", 'r')
data = myFile.readlines()
myFile.close()

day = [] ; sain = []; malade = [] ; imm = []; dead = [] ;

for i in range(0, len(data)):
    ligne = data[i]

    ligne=ligne.rstrip ("\n")


    ligne_data=ligne.split(";")
    day.append(int(ligne_data[0]))
    sain.append(float(ligne_data[1]))
    malade.append(float(ligne_data[2]))
    imm.append(float(ligne_data[3]))
    dead.append(float(ligne_data[4]))


Aday = np.asarray(day)
Asain = np.asarray(sain)
Amalade = np.asarray(malade)
Aimm = np.asarray(imm)
Adead = np.asarray(dead)

plt.title("Resultats de la simulation")
plt.plot(Aday, Asain, label = 'Saines', color = 'green')
plt.plot(Aday, Amalade, label = 'Malades', color = 'red')
plt.plot(Aday, Aimm, label = 'Immunisees', color = 'cyan')
plt.plot(Aday, Adead, label = 'Mortes', color = 'black')
plt.xlabel('Temps en jours', fontsize = 15)
plt.ylabel('Nombre de personnes', fontsize=15)
plt.legend(loc=2, fontsize=12)

plt.show()
