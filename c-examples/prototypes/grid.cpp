// der ganze code ist nicht fehlerfrei bei dem zugriff auf grid kann es an einigen stellen zu out of bound kommen liegt einfach daran das an der stelle wo das abgefangen werden sollte das nicht ausreichend getan wird ist aber net so schlimm hoffe ich


class grid
{
      int grid[][]; //Das Grid halt //zum pointer ändern oder schon geändert
      
      int arrayWidth = 0;
      int arrayHeight = 0;
      
      double increment = 1; //die Strittweite des Grids
      
      
      double posX; //der punkt wo grid[0][0] liegt
      double posY;
      
      double maxX = arrayWidth * increment;
      double maxY = arrayHeight * increment;
      
      //geter und setter noch einfügen für die einzelne werte und so bla bla
      
      double getIncrement(){return increment;}
      double getPosX(){return posX}
      double getPosY(){return posY}
      
      void setGrid(int width, int height, double baseValue)
      {
           int newGrid[width][height];
           for(int i = 0; i < width; i++)
           {
                   for(int j = 0; j < height; j++)
                   {
                           newGrid[i][j] = baseValue;
                   }
           }
           this.grid = newGrid;
           return;
      }
      
      void modifyNearestPoints(double parmX, double parmY, double value[][]) //value soll ein 2x2 array sein in dem die differenz zischen soll und ist stehen
      {
           int indexDL[] = getIndexOfDL(parmX, parmY)//DL steht für Down Left
           grid[ indexDL[0]   ]  [ indexDL[1]   ] = grid[ indexDL[0]   ]  [ indexDL[1]   ] + value[0][0] ; //grid muss hier noch nicht gesetzt sein daher kann das schiefgehen wenn der andere code mist macht aber wir sind mal optimistisch             
           grid[ indexDL[0]+1 ]  [ indexDL[1]   ] = grid[ indexDL[0]+1 ]  [ indexDL[1]   ] + value[1][0];
           grid[ indexDL[0]   ]  [ indexDL[1]+1 ] = grid[ indexDL[0]+1 ]  [ indexDL[1]   ] + value[0][1];
           grid[ indexDL[0]+1 ]  [ indexDL[1]+1 ] = grid[ indexDL[0]+1 ]  [ indexDL[1]   ] + value[1][1];
           return;           
           }
      
      double array[] getNearestPoints(double parmX, double parmY) //gibt die 4 nächsten Werte zurück
      {
             double toReturn[2][2][3];              //die ersten beiden dimmensionen sind für die 4 punkte da um sie zu unterscheiden in ihrer anordung
                                                   // die dritte dimension gibt an was man von dem wert will 0 = Xpos; 1 = Ypos; 2 = wert;
             
             int indexDL[] = getIndexOfDL(parmX, parmY)//DL steht für Down Left
             
             //hole x Werte
             toReturn[0][0][0] = indexDL[0]   * increment + posX
             toReturn[1][0][0] = indexDL[0]+1 * increment + posX
             toReturn[0][1][0] = indexDL[0]   * increment + posX
             toReturn[1][1][0] = indexDL[0]+1 * increment + posX
             
             //hole y Werte
             toReturn[0][0][1] = indexDL[1]   * increment + posY
             toReturn[1][0][1] = indexDL[1]   * increment + posY
             toReturn[0][1][1] = indexDL[1]+1 * increment + posY
             toReturn[1][1][1] = indexDL[1]+1 * increment + posY
             
             //hole die Werte aus dem Array
             toReturn[0][0][2] = grid[ indexDL[0]   ]  [ indexDL[1]   ]; //grid muss hier noch nicht gesetzt sein daher kann das schiefgehen wenn der andere code mist macht aber wir sind mal optimistisch             
             toReturn[1][0][2] = grid[ indexDL[0]+1 ]  [ indexDL[1]   ];
             toReturn[0][1][2] = grid[ indexDL[0]   ]  [ indexDL[1]+1 ];
             toReturn[1][1][2] = grid[ indexDL[0]+1 ]  [ indexDL[1]+1 ];
             
             return toReturn;
             }
      private int array[] getIndexOfDL(double parmX, double parmY)
      {
             int toReturn[2];
              
             double x = parmX - posX;
             double y = parmY - posY;
      
             
             if (x < 0) x = 0;//out of bound abfangen
             if (y < 0) y = 0;
             if (x > maxX) x = maxX;
             if (y > maxY) y = maxY;
             
             //rechne index von ecke unten links aus (hoffe ich zumindestens. ka was ein int cast macht
             int indexX = (int) x / increment;
             int indexY = (int) y / increment;
             
             toReturn[0] = indexX;
             toReturn[1] = indexY;
             
             return toReturn;

              }
       
      }


class mirIstNochKeinNameEingefallenDasWollteBenMachen
{
      double invertFactor = 1; //damit werden aus den abständen factoren empfolen ist 1 aber wurzel 2 wäre auch denkbar alles darüber macht gar keinen sinn denke ich und alles unter wurzel 2 halbe macht auch gar keinen sinn 
      int getExpectedTime(double parmA, double parmB)
      {
          double points[][][] = grid::getNearestPoints(parmX, parmY); //hole die 4 nächsten punkte
          
          double fac[2][2];
          //rechne distanz zwischen punkt und den eckpunkten aus
          fac[0][0] = distanz(points[0][0][0], points[0][0][1], parmA, parmB);
          fac[1][0] = distanz(points[1][0][0], points[1][0][1], parmA, parmB);
          fac[0][1] = distanz(points[0][1][0], points[0][1][1], parmA, parmB);
          fac[1][1] = distanz(points[1][1][0], points[1][1][1], parmA, parmB);
          
          makeDistanzToFactor(fac[][]) //übegebe pointe
          standardizeFactors(fac[][]) 
          
          double toReturn = pointers[0][0][2] * fac[0][0] +
                            pointers[1][0][2] * fac[1][0] +
                            pointers[0][1][2] * fac[0][1] +
                            pointers[1][1][2] * fac[1][1];
          return toReturn;
          }
          
      
      void standardizeFactors(double fac[][])
      {
           //am ende ist die summe der factoren 1
           double facSum = fac[0][0] + fac[1][0] + fac[0][1] + fac[1][1];
           fac[0][0] = fac[0][0] / facSum;
           fac[1][0] = fac[1][0] / facSum;
           fac[0][1] = fac[0][1] / facSum;
           fac[1][1] = fac[1][1] / facSum;
           
           }
      void makeDistanzToFactor(double dist[][])    
      {
           double invertFac = invertFactor * grid::getIncrement();
           dist[0][0] = (invertFac - dist[o][o] >= 0) ? invertFac - dist[o][o] : 0;
           dist[1][0] = (invertFac - dist[1][o] >= 0) ? invertFac - dist[1][o] : 0;
           dist[0][1] = (invertFac - dist[o][1] >= 0) ? invertFac - dist[o][1] : 0;
           dist[1][1] = (invertFac - dist[1][1] >= 0) ? invertFac - dist[1][1] : 0;
           }
      
      double distanz(double x1, double y1, double x2, double y2)
      {
             double disX = x1 - x2;
             double disY = y1 - y2;
             
             //positiv machen
             if (disX < 0) disX = -disX;
             if (disY < 0) disY = -disY;
             //hm das war irgenwie unnötig...
             
             double toReturn = 0//hier muss wurzel aus disX quadrat pus disY quadrat gerechnet werden aber ka wie das jetzt schon wieder geht 
             return toReturn;
             }
      }
