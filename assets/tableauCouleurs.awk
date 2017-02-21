#!/usr/bin/awk -f
#
# ce fichier a pour but de faire un tableau
# affichable par un navigateur qui liste un ensemble
# de couleur connue, et stockée dans le fichier assets/colors.xml

BEGIN {
	compteur = -1;
	FS = "[\"=<>]"
	# Avec les séparateurs : FS = "[\"= <>]"
	# Ici on a le nom de la couleur comme étant $4
	# les valeurs des couleurs sont sur $3
	fichierSortie = "o_mon_beau_tableau.html";
	table= "<h1>Auteurs : BARDOUX Laurent, SULTAN Charles, GHESH Mehdi</h1>"\
		   "<table>"\
		   "<tr><th>Nom</th><th>Apercu</th><th>Valeurs RGB</th></tr>"

	bgcolor[0] = "#FFFFFF";
	bgcolor[1] = "#F7F7F7";
	cptBg = 0;
}

{
	if($2 == "couleur name")
	{
		compteur = 0;
		colorName = $4;
		tdBgColor = "(";
	}
	else if(compteur >= 0)
	{
		if(compteur != 2)
		{
			tdBgColor = tdBgColor $3 ","
			compteur++;
		}
		else
		{
			tdBgColor = tdBgColor $3 ")"
			compteur = -1;

			table = table "<tr bgcolor=\"" bgcolor[cptBg] "\" height=\"20\">" \
					        "<td width=\"100\"><div align=\"left\">"colorName"</div></td>" \
					        "<td width=\"100\" style=\"background-color:rgb"tdBgColor"\"></td>" \
					        "<td><div align=\"right\">"tdBgColor"</div></td>" \
					      "</tr>";
			
			cptBg = (cptBg+1) % 2;
		}
	}
}

END {
	table = table "</table>";
	print table > fichierSortie;
	system("firefox " fichierSortie);
	print "Suppression du fichier temporaire généré : " system("rm " fichierSortie);
}