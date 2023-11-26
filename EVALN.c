/*función que evalúe expresiones postfijas. Para ello, será necesario definir
   y utilizar de nuevo el tipo EXPRESION del ejercicio anterior. Nuevamente, deberá utilizarse el TAD
   PILA.*/
   
#include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <ctype.h>
  #define MAX 10
  
  typedef struct
  {
  	float item[MAX];
  	int top;
  }PILA;

  //Prototipos de funciones
  void push (float);
  void mostrar(PILA);
  void conversion();
  void detalles();
  int menu();
  PILA iniciar(PILA);
  int empty(PILA);
  int oper(char);
  float pop();
  float ecuacion(float,float,char);
  
  //Variables Globales
    PILA Tad_Pila;
    char expre[MAX];
    int i,j,cont[6];
    float resul;
    
    main()
    {
    	int opc,op;
    	Tad_Pila=iniciar(Tad_Pila);
    
       do
    	{
    	   system("cls");
    	   
    	   for(j=0;j<=6-1;j++) //inicializar los contadores
    	     cont[j]=0;
    	   
    	   conversion();
    		
    	   system("cls");
    	   
    	   opc=0;
    	   while(opc!=3)
    	   {
    	   	 system("cls");
    		 opc=menu();
    		
    		 system("cls");
    	     switch(opc)
    	     {
    	        case 1: printf("\n");
    	                detalles();
			            system("pause");
					    break;
			   
			    case 2:printf("\n");
			           mostrar(Tad_Pila);
			           printf("\n \t\t %c Expresion: %s %c \n",174,expre,175);
    	               system("pause");
    	               break;
    	        
    	        case 3: break;
    	              
    	        default: printf("\t\t ERROR: opcion no valida \n");
    	                  break;
			} 
		   }
    	     Tad_Pila=iniciar(Tad_Pila);
    	     printf("\n");
    	     
    	 printf("\t Desea Salir \n\t 1.Salir \n\t 2.Continuar \n");
    	 printf("\t opcion:");
    	 scanf("%d",&op);
		}while(op==2);
	
	 return 0;
	}
	
   //funciones
   
   //Inicializo la pila
   PILA iniciar(PILA pl)
   {
   	 pl.top=-1;
   	 
   	 return pl;
   }
  
   //verificacion de pila vacia---------------------------------------------------------------------------------------------------------------------------------------------
  int empty(PILA pl)
  {
  	 int res;
  	 
  	 if(pl.top==-1)
  	   res=1;
  	 else
  	  res=0;
  	  
  	 return res; 
  }
  
  //Push -----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  void push(float n)
  {

  	 if(Tad_Pila.top==MAX-1)
  	   printf("\n\t %c Desbordamiento %c \n",254,254);
  	 else
  	  {
		Tad_Pila.item[++Tad_Pila.top]=n;	
	  }
	  
	return;
  }
  
  //POP -------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   float pop()
  {
  	 float x;
  	 
  	 printf("\n\n");
  	 
  	 if(empty(Tad_Pila)==0)
  	  {
  	  	x=Tad_Pila.item[Tad_Pila.top--];
	  }
	 else
	   printf("\t\t %c Subdesborde %c \n\n",254,254);
	   
	return x;
  }
  

  //verifica si un caracter es un operador -----------------------------------------------------------------------------------------------------------------------------------------
  int oper(char c) 
  {
  	int res; 
  	
    if (c == '+' || c == '-' || c == '*' || c == '/');
      res=1;
      
    return res;
  }

  //realiza los calculos -----------------------------------------------------------------------------------------------------------------------------------------------------------
  float ecuacion(float n1,float n2,char op)
  {
  	 float con;
  	 
  	switch(op)
  	 {
  	    case '+': con=n1+n2;
  	              cont[2]++;
		          break;
		          
		case '-': con=n1-n2;
		          cont[3]++;
		          break;
		          
		case '*': con=n1*n2;
		          cont[4]++;
		          break;
		
		case '/': if(n2!=0)
		          {
		            con=(float)n1/n2;
		            cont[5]++;
		          }
		          else
		            con=-999;
		           break;
		default: con=-999;
		         break;
	 }

	 return con;
  }
  
  //Mostrar pila  -------------------------------------------------------------------------------------------------------------------------------------------------------------------
  void mostrar(PILA pila)
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
  	 	   printf("\t [%d] \t |  %.2f  | \n",i,pila.item[i]);	
  	 	   printf("\t\t \t\t -------- \n");
		 }  
	 }
	return;	
  }
  
  //solucion de la expresion  ---------------------------------------------------------------------------------------------------------------------------------------------
  void conversion()
  {
  	 int leng,val;
	 float opr2,opr1;

  	  printf("\t\t -> Bienvenidos <- \n\n");
      printf("\n\t -> Ingrese una expresion postfija: ");
      fflush(stdin);
      gets(expre);
    		
      leng=strlen(expre);
    		
    	j=0;
        while (j<=leng-1) 
		{
    	   if(isdigit(expre[j]))
    		{
    		   val=expre[j]-'0';
    		   push((float)val);
    		   cont[0]++;
    	    }
    		else
    		{
    		  if(oper(expre[j])==1)
    		   {
    		     opr2=pop();
    		     opr1=pop();
    		     resul=ecuacion(opr1,opr2,expre[j]);
    		     push((float)resul);
    		     cont[1]++;
			  }
		      if(resul==-999)
			  {
				printf("\n\t\t ->ERROR: caracter no leible \n");
				break;
    		  }
    		}
    	 j++;
    	}

     printf("\t\t --> Resultado:  %.2f <-- \n\n",resul);
     system("pause");
     
    return;
  }
  
  //Detalles  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  void detalles()
  {
  	 printf("\t\t %c Detalles %c \n\n",254,254);
  	 printf("\t -> Resultado : %.2f \n",resul);
  	 printf("\t -> Cant. Numeros: %d \n",cont[0]);
  	 printf("\t -> Cant. operaciones: %d \n",cont[1]);
  	 printf("\t -> Cant.Suma: %d \n",cont[2]);
  	 printf("\t -> Cant.Resta: %d \n",cont[3]);
  	 printf("\t -> Cant.Mult : %d \n",cont[4]);
  	 printf("\t -> Cant.Div: %d \n",cont[5]);
  	 
  	 printf("\n");
  	 
  	 return;
  }
  
   //Menu de opciones -----------------------------------------------------------------------------------------------------------------------------------------------------------------
  int menu()
  {
  	int op;
  	
  	printf("\t\t -> M E N U <- \n\n");
  	printf("\t 1.Detalles \n");
  	printf("\t 2.Estado de la Pila \n");
  	printf("\t 3.Continuar \n");
  	printf("\t Opcion:");
  	scanf("%d",&op);
  	
  	return op;
  }
