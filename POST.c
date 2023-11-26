/*programa que convierta una expresión infija formada por operandos y operadores aritméticos simples en una expresión postfija equivalente.
  Para ello, será necesario definir el tipo EXPRESION, y establecer un mecanismo para obtener del usuario una expresión infija y depositarla 
  en memoria en una variable de tipo EXPRESION. Deberá definirse y utilizarse el TAD PILA, cuyos elementos serán operadores. */ 
  
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <ctype.h>
  #define MAX 20
  
   typedef struct
   {
   	  char item[MAX];
   	  int top;
   }EXPRESION;
   
   //Prototipo de funciones
   EXPRESION push (EXPRESION,char);
   char pop(EXPRESION);
   char tope(EXPRESION);
   void conver();
   void mostrar(EXPRESION,char[]);
   int prior(char);
   int menu();
   int empty(EXPRESION);
   int oper(char);
   
   //Variables Globales
   EXPRESION inf,Tad_Pila;
   char Post[MAX];
   int i,j,k;
   
    main()
    {
      int opc,op;
    	
    	do
    	{
    		inf.top=-1;
    		
    		system("cls");
    		conver();
    		
    		opc=0;
    	    while(opc!=3)
    	    {
    		   system("cls");
    		   opc=menu();
    		 
    		   system("cls"); 
    		   switch(opc)
    		    {
    		 	     case 1: printf("\n");
    		 	             mostrar(inf,Post);
    		 	             printf("\n");
    		 	             system("pause");
    		 	             break;
    		 	
    		          case 2: printf("\n");
    		 	              printf("\t\t --Tope-- \n");
    		 	              printf("\t\t Infija \n");
    		 	              printf("\t\t   %c \n",tope(inf));
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
	
	//Funciones
	
	//Push ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   EXPRESION push(EXPRESION p, char n)
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
   int empty(EXPRESION pl)
   {
  	 int res;
  	 
  	 if(pl.top==-1)
  	   res=1;
  	 else
  	  res=0;
  	  
  	 return res; 
   } 
   
    //Pop ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  char pop(EXPRESION pil)
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
  char tope(EXPRESION con)
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
  
   //Resolucion de operacion ------------------------------------------------------------------------------------------------------------------------------------------------------
   void conver()  
   {
   	 int leng,indiPo=0;
   	 char carac,temp;
   	 char expre[MAX];
   	 
   	 Tad_Pila.top=-1;
    
     system("cls");
     
	 printf("\n\t\t --> Bienvenido <-- \n");	
     printf("\n\t -> Ingrese una expresion: ");
     fflush(stdin);
     gets(expre);
     
     leng=strlen(expre);
    		
     for(j=leng-1;j>=0;j--)
    	 inf=push(inf,expre[j]);
    	 
     for(k=inf.top;k>=0;k--)
     {
     	carac=inf.item[k];
     	  
     	if(isalnum(carac)) //En caso de operando , pasa directamente a la expresion
     	  Post[indiPo++]=carac;
     	else
     	{
     	   if(oper(carac)==1)
     	    {
     	      //Si es un operador ,proceso la procedencia
			   while(empty(Tad_Pila)!=1 && prior(tope(Tad_Pila)) >= prior(carac))
			   {
			   	  Post[indiPo++]=Tad_Pila.item[Tad_Pila.top--];
			   }
			   
			    Tad_Pila=push(Tad_Pila,carac); 	
			}
			else
			 {
			 	if(carac=='(')
			 	  Tad_Pila=push(Tad_Pila,carac);
			 	else
			 	 {
			 	 	if(carac==')')
			 	 	{
			 	 	  while(tope(Tad_Pila)!= '(')
					  {
						 Post[indiPo++]=Tad_Pila.item[Tad_Pila.top--];
					  }	
					  pop(Tad_Pila);  //desaparesco los parentesis
					  Tad_Pila.top--;
					}
				 }
			 }
		}	 
	 }
	  
	 //Vacio los operadores restantes de la pila
	 for(i=Tad_Pila.top;i>=0;i--)
	   Post[indiPo++]=Tad_Pila.item[i];
	   
    printf("\n\n");
    	     
    printf("\t\t --> %s <-- \n",Post);
    
	system("pause");
		    
    return;
   }
   
   //Mostrar pila ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  void mostrar(EXPRESION pila,char pre[])
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
  	 	   printf("\t [%d] \t |  %c  | \t |  %c  | \n",i,pila.item[i],pre[i]);	
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
