#include<iostream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include <initializer_list>
#include "include/JsonBox.h"
#include "srct/UnitTest++.h"


#define		CODIGO_DESCONTO_INEXISTENTE	2;
#define 	PRODUTO_INEXISTENTE		1;
#define		OK				0;


#define		MAXIMUM_NUMBER_CHARACTERS_TEST_PRODUCTID	30	
#define		NUMBER_VALIDATE_PRODUCT_ID_TESTS		 5


using namespace std;
using namespace JsonBox;




// Classe que representa o produto em si
class Product 

 {
     
 
   public:

    Product(unsigned id,string Name , double Price) 
         {
           ID = id;
           name = Name;
           price = Price;
         }


    void setNextProduct(Product * pointer)
      {
         nextProduct = pointer;
      }


    unsigned getID()
       {
         return ID;
       }

    string getName()         
       {
         return name;
       }
        
    double getPrice()
       {
         return price;
       }
   

   Product * getNextProduct()
      {
        return nextProduct;
      }

  
 
                       
   private : 
    unsigned ID;     
    string name;
    double price;
    Product* nextProduct;

 };




// Classe que representa o carrinho de compras
class Shoppingcart
  {
                
  
   public:

  // Constructor

    Shoppingcart()
         {
             
             firstProduct = NULL;
             ancientProduct = NULL;
             currentProduct = NULL;
          
         }


  //  Setters e Getters

   double getDiscount()
         {
            return discount;
         }

   Product * getFirstProduct()
         {
            return firstProduct;
         }

  
   void setTotalPrice()
        {
          
           Product* sweeper = firstProduct;
           double suM=0;
         if(sweeper != NULL)
          {
           while(sweeper->getNextProduct() != NULL)
            {
               suM += sweeper->getPrice();
               sweeper = sweeper->getNextProduct();
            }   
             suM += sweeper->getPrice();
          }
          sum = suM;           


        } 


    double getTotalPrice()
        {

          return sum;

        }



  // Metodo que gera calcula os descontos sejam eles percentuais ou fixos
     unsigned setDiscount(string couponCode , Array & ar2)
   
        {

           unsigned i = 0;
           bool foundDiscount = false;
        

            while(i<ar2.size())
               {
                     if(couponCode == ar2[i]["code"].getString())
                       {
                          foundDiscount = true;

                              if(ar2[i]["type"].getString() == "fixed")
                               {       
                                   fixedDiscount = true;
                                   discount = ar2[i]["amount"].getDouble();
                               }
                               else
                               {
                                 //  cout<<"Hier bettretten "<<endl;
                                   fixedDiscount = false;
                                   discount = ar2[i]["amount"].getDouble();
                                   discount = (discount/100)*sum;
                               } 
                       }
                i++;

               }


            
           if(!foundDiscount)
            {
             cout<<"O desconto nao foi encontrado "<<endl;
             return CODIGO_DESCONTO_INEXISTENTE;
            }
 
 
           return OK;

        }



            
   // Metodo que adiciona um objeto produto ao objeto da classe Shoppingcart que nada mais e do que uma lista encadeada
      unsigned addToShoppingCart(unsigned productID,Array & ar)
        {
           
           bool productExists = false;
           unsigned short i=0;
           unsigned teste;
           
           // parte do codigo que verifica se o codigo do produto representa um produto existente e que faz adicao 
          
         
             while(i<ar.size() && !productExists)
               {

                   
                     if(ar[i]["id"].getInt() == productID && firstProduct == 0)
                      {
                       currentProduct = new Product(ar[i]["id"].getInt(),ar[i]["name"].getString(),ar[i]["price"].getDouble());
                       ancientProduct = currentProduct;
                       firstProduct = currentProduct;
                       currentProduct->setNextProduct(NULL);
                       productExists = true;
                      }

                     else if(ar[i]["id"].getInt() == productID && firstProduct != 0)
                      {
                         currentProduct = new Product(ar[i]["id"].getInt(),ar[i]["name"].getString(),ar[i]["price"].getDouble());
                         ancientProduct->setNextProduct(currentProduct);
                         ancientProduct = currentProduct;
                         currentProduct->setNextProduct(NULL);
                         productExists = true;
                      }
                         
                          
                   i++;     
   

 
               }

    

            if(!productExists)
                {
                    cout<<"O produto nao existe "<<endl;
                    return PRODUTO_INEXISTENTE;
                }
             


            return OK;

        }





 // Metodo que verifica se a entrada productID eh um inteiro sem sinal e caso nao seja retorna falso , usada para validacao

  bool validateProductID(string productID)
    {
 
       unsigned i=0;
       bool idValido = true;
 
 // Vamos de 1 em 1 caracter procurando por pontos virgulas e sinais de menos , se forem encontrados o formato do numero eh invalido
       while(i<productID.size() && idValido)
          {
                 if(productID[i] != '0' && productID[i] != '1' && productID[i] != '2' && productID[i] != '3' 
                    && productID[i] != '4' && productID[i] != '5' && productID[i] != '6' && productID[i] != '7'
                     && productID[i] != '8' && productID[i] != '9')
                        idValido = false;
            
           i++;
          }
              
       return idValido;
    }




 // Metodo que exibe na tela o resumo das compras feitas e o valor total e o desconto
     void  purchaseResume()

    {
        
      Product * sweeper = firstProduct;
      
      setTotalPrice();
   
      if(sweeper !=NULL)
      {
            while (sweeper != NULL)
             {
        
              cout<<sweeper->getID()<<"  "<<sweeper->getName()<<"  "<<setprecision(2)<<fixed<<sweeper->getPrice()<<endl;
              cout<<endl;
              sweeper = sweeper->getNextProduct();
             }
         


     cout<<endl;
     cout<<endl;

           if(fixedDiscount)
            {
             cout<<"Descontos:   -"<<setprecision(2)<<fixed<<discount<<endl;
             cout<<endl;
             sum -= discount;
             cout<<"Total:        "<<setprecision(2)<<fixed<<sum<<endl;
            }
          else
            {
            cout<<"Descontosp:   -"<<setprecision(2)<<fixed<<discount<<endl;
            cout<<endl;
            sum -= discount;
            cout<<"Total:        "<<setprecision(2)<<fixed<<sum<<endl;
            }

 
     }             

   }



   private:

    Product* firstProduct;
    Product* ancientProduct;
    Product* currentProduct;
    double discount;
    double sum;
    bool  fixedDiscount;              // Variavel booleana verdadeira quando o desconto eh fixo
      

         
  };  





// Inicio da parte do codigo que implementa 2 funcoes de uso geral que nao estao implementadas dentro de classes


// Funcao que faz a mesma coisa que atoi fazia em C
 unsigned Atoi (string productID)
  
     {

        unsigned i = 0;
        char * auxProductID = new char [productID.size() + 1];
        
        while(i<productID.size())
          {
            auxProductID[i] = productID[i];
            i++;
          }

        auxProductID[i] = '\0';    
        

        return (unsigned) atoi(auxProductID);      


     }

// Fim da funcao que faz a mesma coisa que atoi faz em C




// Funcao que implementa uma importante funcionalidade que precisamos , saber se um valor esta dentro de um conjunto de valores
bool is_in_09(char productID)
{
    unsigned short i;
    for (i = 0 ; i<10 ; i++) 
         if(productID == (char) i)
               return true;      
    
    return false;
}
// Fim da funcao que implementa a funcionalidade estar contido num conjunto

// Fim da parte do codigo que implementa 2 funcoes de uso geral que nao estao implementadas dentro de classes





 // Comeco da parte do programa que so realiza testes , o motivo de estarmos escrevendo este .cpp


 /* Funcao que testa a capacidade do metodo "addToShoppingCart()" em adicionar corretamente produtos ao carrinho de compras
    obtidos de product.json */ 

 TEST(addToShoppingCart)
   {

       
       bool error = false;
       unsigned short i = 0;
       Shoppingcart* shoppingCart = new Shoppingcart();
       Value v;
       Array ar;
       Product * sweeper;
       v.loadFromFile("product.json");
       ar = Array(v.getArray());
       
     
       

   while(i<ar.size())
   {
    shoppingCart->addToShoppingCart((unsigned) ar[i]["id"].getInt() , ar);
    i++;
   }   

   sweeper = shoppingCart->getFirstProduct();       
   do
   {
   i=0;
   unsigned short numberOfOcurrences = 0;
       while(i<ar.size())
       {
 
            if(sweeper->getID() == (unsigned)ar[i]["id"].getInt() && sweeper->getName() == ar[i]["name"].getString()  && 
               sweeper->getPrice() == ar[i]["price"].getDouble())      
                      numberOfOcurrences++;
        i++;
       }

       if(numberOfOcurrences != 1)
              CHECK(false);
 
    sweeper = sweeper->getNextProduct();
   }
   while(sweeper->getNextProduct() != NULL );     


  delete shoppingCart;
  
  

  }

 // Fim da funcao que testa o metodo addToShoppingCart() da classe Shoppingcart 






// Funcao que testa o metodo setDiscount()

TEST(setDiscount)

 {


 
  unsigned short i = 0;
  double sum = 0;
  string couponCode;
  Shoppingcart* shoppingCart = new Shoppingcart();
  Value v;
  Value v2;
  Array ar;
  Array ar2;
  v.loadFromFile("product.json");
  v2.loadFromFile("discounts.json");
  ar = Array(v.getArray());
  ar2 = Array(v2.getArray());

 // cout<<"Veja v "<<&v<<endl;
     


   while(i<ar.size())
   {
    shoppingCart->addToShoppingCart((unsigned) ar[i]["id"].getInt() , ar);
    i++;
   }   

  // cout<<"Togar "<<endl;
   i=0;  

   while(i<ar.size())
   {
    sum += ar[i]["price"].getDouble();                
    i++;
   }

 //  cout<<"getTotalPrice() and sum "<<setprecision(2)<<fixed<<shoppingCart->getTotalPrice()<<" "<<setprecision(2)<<fixed<<sum<<endl;

   i=0;

   shoppingCart->setTotalPrice();

   while(i<ar2.size())
   {
        shoppingCart->setDiscount(ar2[i]["code"].getString(),ar2);
        
               if(ar2[i]["type"].getString() == "percentage")
                  {
                   double percentFraction = ar2[i]["amount"].getDouble();
                   percentFraction /=100;
                   double discount = sum*percentFraction;
                      if(shoppingCart->getDiscount() != discount)
                               CHECK(false);
                  }
                else
                  {
                    double discount = ar2[i]["amount"].getDouble();  
                       if(shoppingCart->getDiscount() != discount)
                                CHECK(false);
                  }
   i++;

   }

       delete shoppingCart;

 } 

// Fim da funcao que testa o metodo setDiscount







 // Funcao que testa o metodo validateProductID() 

TEST (validateProductID)

{
      unsigned short i = 0;
      unsigned short j = 0;
      unsigned short numberOfCharactersString;
      bool testFunctionStringFalseResult = false;    // a gente supoe aqui que a string gerada aleatoriamente sera valida
      Shoppingcart* shoppingCart = new Shoppingcart();
      char * c = new char[2];
   

      srand(time(NULL));

 while(j<NUMBER_VALIDATE_PRODUCT_ID_TESTS)
  {
     
      
      string productID;
   

      numberOfCharactersString = rand() % MAXIMUM_NUMBER_CHARACTERS_TEST_PRODUCTID;
     

      while(i< numberOfCharactersString)
       {
        c[0] = (char)(rand() % 128);
        c[1] = '\0';
        productID.append(c,1);
        i++;
       }

   

       i=0;
 

  

       while(i<numberOfCharactersString && !testFunctionStringFalseResult)
        {
         
         testFunctionStringFalseResult = !is_in_09(productID[i]); /*Funcao criada para testar se */
         i++;                                                          /* productID[i] esta dentro do conjunto */
        }

        i = 0;

       
 
        if(shoppingCart->validateProductID(productID) == testFunctionStringFalseResult) // Como o metodo da classe shoppingCart e 
                     CHECK(false);                                                      // a funcao is_in_09() trabalham de forma
                                                                                        // diferente na verdade o teste indica uma
  j++;                                                                                  // falha se seus resultados booleanos forem
  }                                                                                     // iguais

  delete shoppingCart;

}
// Fim da funcao que testa o metodo validateProductID



// Fim das funcoes que implementam testes




// Inicio da funcao principal     
     
int main ()
     {

   return UnitTest::RunAllTests();;   
            
     }         






