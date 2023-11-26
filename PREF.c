/*programa que convierta una expresión infija formada por operandos y operadores aritméticos simples
 en una expresión prefija equivalente. Para ello, es necesario definir el tipo EXPRESION, y establecer un mecanismo para obtener del
 usuario una expresión infija y depositarla en memoria en una variable de tipo EXPRESION. Deberá
 definirse y utilizarse el TAD PILA, cuyos elementos serán operadores.*/
 
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #define MAX 20
  
  typedef struct
  {
  	char item[MAX];
  	int top;
  }PILA;

  //Prototipos de funciones
  PILA push (PILA,char);
  char pop(PILA);
  char tope(PILA);
  void conversion();
  void mostrar(PILA,PILA);
  int prior(char);
  int menu();
  int empty(PILA);
  int oper(char);
  
  //Variables Globales
    PILA expresion,Tad_Pila,prefija;
    int i,j;
    
    main()
    {
    	int opc,op;
    	
    	do
    	{
    		expresion.top=-1;
    		prefija.top=-1;
    		
    		system("cls");
    		conversion();
    		
    		opc=0;
    	    while(opc!=3)
    	    {
    		  system("cls");
    		  opc=menu();
    		 
    		   system("cls"); 
    		   switch(opc)
    		   {
    		 	   case 1: printf("\n");
    		 	           mostrar(expresion,prefija);
    		 	           printf("\n");
    		 	           system("pause");
    		 	           break;
    		 	
    		 	    case 2: printf("\n");
    		 	            printf("\t\t --Topes-- \n");
    		 	            printf("\t\t Infija \t Prefija \n");
    		 	            printf("\t\t   %c  \t\t  %c \n",tope(expresion),tope(prefija));
    		 	            system("pause");
    		 	            break;
    		 	        
    		 	    case 3: break;
    		 	
    		 	    default: printf("\t\t ERROR: opcion no valida \n");
    		 	           break;
			 }
	      }   
	
		  printf("\n\t Desea Salir \n\t 1.Salir \n\t 2.Continuar \n");
    	 printf("\t opcion:");
    	 scanf("%d",&op);
		}while(op==2); 
	
	 return 0;
	}
   //funciones
   
   //Push --------------------------------------------------------------------------------------------------------------------------------------------------------------
  PILA push(PILA p, char n)
  {

  	 if(p.top==MAX-1)
  	   printf("\n\t %c Desbordamiento %c \n",254,254);
  	 else
  	  {
		p.item[++p.top]=n;	
	  }
	  
	return p;
  }
  
   //verificacion de pila vacia -------------------------------------------------------------------------------------------------------------------------------------------
  int empty(PILA pl)
  {
  	 int res;
  	 
  	 if(pl.top==-1)
  	   res=1;
  	 else
  	  res=0;
  	  
  	 return res; 
  }
  
  //Pop ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  char pop(PILA pil)
  {
  	 char x;
  	 
  	 printf("\n\n");
  	 
  	 if(empty(pil)==0)
  	  	x=pil.item[pil.top--];
	 else
	   printf("\t\t %c Subdesborde %c \n\n",254,254);
	   
	return x;
  }
  
  //StackTope ---------------------------------------------------------------------------------------------------------------------------------------------------------------
  char tope(PILA con)
  {
  	char tan;
  	
  	  tan=con.item[con.top];
  	   
  	return tan;
  }
  
  //verifica si un caracter es un operador -----------------------------------------------------------------------------------------------------------------------------------
  int oper(char c) 
  {
  	int res; 
  	
    if (c == '+' || c == '-' || c == '*' || c == '/')
      res=1;
     else
       res=0;
       
    return res;
  }
  
  //Verificacion de procedencia -------------------------------------------------------------------------------------------------------------------------------------------------
  int prior(char operador)
  {
  	int pr;
  	
    if (operador == '+' || operador == '-') {
        pr=1;
    } else if (operador == '*' || operador == '/') {
        pr=2;
    }
    return pr; 
  }
  
  //Realizacion de la expresion ----------------------------------------------------------------------------------------------------------------------------------------------------
  void conversion()
  {
  	 int leng,indP=0;
     char expre[MAX],com,temp;
     char prefi[MAX];
	 int ini,fin;
	 	
     Tad_Pila.top=-1;
    
     system("cls");
     
	 printf("\n\t\t --> Bienvenido <-- \n");	
     printf("\n\t -> Ingrese una expresion: ");
     fflush(stdin);
     gets(expre);
      		
     leng=strlen(expre);
    		
     for(j=0;j<leng;j++)
    	 expresion=push(expresion,expre[j]);
     
     for (j=expresion.top;j>= 0;j--)
	  {
        com= expresion.item[j];

       if(oper(com)==1)
		{		
            // Es un operador, procesamos la pila de operadores   
            while(empty(Tad_Pila)!=1 && (prior(tope(Tad_Pila)) > prior(com)))
            {
                prefi[indP++]=Tad_Pila.item[Tad_Pila.top--];
            }
            Tad_Pila=push(Tad_Pila,com);  
        }
        else
          {
          	if(com==')')
          	  Tad_Pila=push(Tad_Pila,com);
          	 else
          	  {
          	  	if(com=='(' )
          	  	{
			       while(tope(Tad_Pila)!=')') 
				   {
                      prefi[indP++]=Tad_Pila.item[Tad_Pila.top--];
                   }
                   pop(Tad_Pila);  // Deshacerse del '('
                   Tad_Pila.top--; //Deshacerse del )
                }
                else
                 prefi[indP++] = com;
               }
		    }
        }
      
       // Se vacia la pila donde guardo los operadores
        for(i=Tad_Pila.top;i>=0;i--)
		{
          prefi[indP++]=Tad_Pila.item[i];
        }
        
  
      //Invertimos la expresión prefija para obtener el resultado correcto
      ini=0;
      fin=indP-1;
      
       while (ini< fin) 
	   {
        temp = prefi[ini];
        prefi[ini] = prefi[fin];
        prefi[fin] = temp;
        ini++;
        fin--;
       }
   
    leng=strlen(prefi);
    
	//Pila Prefija	     
	for(j=0;j<leng;j++)
    	 prefija=push(prefija,prefi[j]);
    printf("\n");
    	     
    printf("\n \t\t --> %s <-- \n",prefi);
    
	system("pause");
		    
     return;
   }
   
   
  //Mostrar pila ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  void mostrar(PILA pila,PILA pre)
  {
  	
  	if(empty(pila)==1)
  	  printf("\t\t\t %c Pila Vacia %c \n",254,254);
  	else
  	 {
  	    printf("Cima --> \t");
  	    
  	 	for(i=pila.top;i>=0;i--)
  	 	{ 
  	 	   if(i<pila.top)
  	 	      printf("\t\t");
  	 	   printf("\t [%d] \t |  %c  | \t |  %c  | \n",i,pila.item[i],pre.item[i]);	
  	 	   printf("\t\t \t\t ------  \t -------- \n"); 
		}  
	 }
	return;
  }
  
  //Menu -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  int menu()
  {
  	 int con;
  	 
  	 printf("\n\t\t %c M-E-N-U \n\n");
  	 printf("\t 1.Mostrar Pila \n");
  	 printf("\t 2.Cima de Pila \n");
  	 printf("\t 3.Continuar \n");
  	 printf("\t Opcion:");
  	 scanf("%d",&con);
  	 
  	 return con;
  }
