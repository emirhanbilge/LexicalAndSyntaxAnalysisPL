/*

					
				                                           * * *
				                                         * start *
				                                         *       *	
				                                           * * *
	-----------------------------------------------------------------------------------------------------------------------------------
        |            |                 |                                             |							|
    **********      **************    ************	                  **********************				       *******************
   | variable;|     | variable++; |  | ++variable; |	             | variable:=expression; |				       | Special Keyword |
    **********      **************    ************	                  **********************				       *******************
        \		  |	           /                               /          	      \
    	 \		  |	          /                               /                    \
    	  \               |		 /	                         /	                \
    	   \		  |		/			        /                        \
	       **********************		        ********************                   ***********************
	       |	            |                   | with parentheses |                   | without parentheses |
	       |Endofline check and |			    ********************	               ***********************
	       |	            |			    /      \				       /           \
	       ********************** 		           /	    \				      /	            \
					       ****************     ********************   	****************      ********************
				           | with variable |    | without variable |   	| with variable |     | without variable |
					       *****************    ********************   	*****************     ********************
						       \		  /			       |                 /     |        \
							\		 /			       |		/      |         \
							**********************		      ******************   ********* *********** ***********
							| Remove parentheses |            | Remove variable|   | Error | | Integer | | String  |
							**********************		      ******************   ********* *********** ***********		
								 |			       /       |        \       
						       **************************      *********    ***********   ***********           
						       |Make inside the brackets|      | Error |    | Integer |   | String  |
						       **************************      *********    ***********   ***********	
						         /        |           \
							/         |            \
						       /          |             \
				          *********    ***********   ***********
				         | Error |    | Integer |   | String  |
				         *********    ***********   ***********	


//When the code read is analyzed lexicallyand passed successfully, it enters the syntax code.Syntax code has the tree structure specified aboveand the working logic of this tree structure is explained below.
//It represents the beginning of the code in the given tree structure (start). There are basically 5 situations we might encounter when starting to write any line (or code) of code:
//1.variable; -> In this case, it means that not initialize has been made in the written variable and only the existence of this variable has been defined in the code.
//2.variable++(--);->In this case, it may be increased or decreased provided that it is a variable integer previously defined in the code.
//3. (-) ++variable->In the case shown, it is started with an operator, not a variable, and if the specified variable is integer, changes can be made on the variable without any problem.
//4.variable: = term -> In this case, a value change is made on the defined variable. At this point, the type of the variable should be determined. While determining this type, make sure that the statement next to it is correct.
//We can say that the 4th stage is a very complicated stage. At this stage, the term variety we have is quite high. As seen in the tree above, term varieties can be basically divided into two, with and without parentheses.
//Even if we divide term types into two at the 4th stage, it still has a diversity within itself.
//If a term in the 4th stage contains parentheses in itself: it is checked whether it contains variable or not.
//In the 4th stage, if there is variable depending on this, control of each data is provided without removing the parentheses, it is decided which type the variable has. After this decision, the parentheses are removed.
//As a result of removing the parentheses, the variable type of the expression is decided. It can have 3 types: Integer, String or Error (It can be using String and Integer together or using an undefined variable in it.).
//Another type in the 4th stage is a term with brackets and no variables: In that case, the parentheses can be removed directly. Here, the parentheses only provide process priority for us, but the result of the process is not important in the design.
//Here, when the parentheses are removed, the remaining operations are checked and as a result, the variable type of the expression is decided. It can have 3 types: Integer, String or Error (It may be using String and Integer together or using an undefined variable in it.).
//If a term in stage 4 does not contain parentheses in itself : We can divide it again into two : term with Variable and without Variable.
//If a term in stage 4 contains variable and without a parenthesis, the variable in term is parsed and the action will be made as if the variable does not exist.
//At this point, even when there is no variable, term is scanned within itself againand can have 3 kinds of output : String, Integer or Error.
//The 5th stage is the start with specialkeyword. In this case, special keywords recognized by our language were determined and some conditions were written by creating various groups on the determined keywords.

//Okunan kod lexical olarak analiz edildiğinde ve başarılı ile geçtiğinde syntax koduna girmektedir. Syntax kodu yukarıda belirlenen ağaç yapısına sahiptir ve aşağıda bu ağaç yapısının çalışma mantığı açıklanmaktadır.
//Verilen ağaç yapısındaki (start) kodun başlangıcını temsil etmektedir. Herhangi bir kod satırı(veya kodu) yazmaya başlarken karşılabileceğimiz temelde 5 durum bulunmaktadır: 
//1.variable; --> Bu durumda tanımlanan değişkenin içerisinde herhangi bir tanımlanma yapılmamış ve yalnızca bu değişkenin varlığı kod içerisinde tanımlanmış durumdadır.
//2.variable++(--); --> Bu durumda ise önceden kod içerisinde tanımlanmış olan bir variable integer olmak koşulu ile arttırılmış veya azaltılmış olabilir.
//3.(--)++variable --> Gösterilen durumda bir variable ile değil bir operator ile başlanmış ve belirlenen değişkenin integer olması durumunda herhangi bir sorun olmadan değişken üzerinde değişiklik yapılabilir.
//4.variable:=term --> Bu durumda tanımlanan variable üzerinde değer değişikliği yapılmaktadır. Bu noktada variable'ın tipi belirlenmelidir. Bu tip belirlenirken, yanındaki term doğruluğundan emin olunmalıdır.
//4. aşama oldukça karışık bir aşamadır diyebiliriz. Bu aşamada elimizde ki term çeşitliği oldukça fazladır. Yukarıda tree de de görüldüğü üzere term çeşitleri: parantezli ve parantezsiz olarak temelde ikiye ayrılabilir.
//4. aşamada term çeşitlerini temelde ikiye ayırsakta aslında halen kendi içerisinde bir çeşitliliğe sahiptir. 
//4. aşamadaki bir term eğer kendi içerisinde parantez barındırıyorsa: içerisinde variable bulunduruyor mu yoksa bulundurmuyor mu kontrolü yapılır.
//4. aşamada buna bağlı olarak variable bulunuyor ise parantezler kaldırılmadan her bir verinin kontrolü sağlanır variable hangi tipe sahipmiş karar verilir. Bu kararın ardından parantezler kaldırılır.
//Parantezlerin kaldırılması sonucunda da term'ün değişken tipine karar verilir.3 tipe sahip olabilir: Integer , String veya Error(String ve Integer'ın birlikte kullanılması veya içerisinde tanımlanmamış variable kullanımı olabilir.).
//4. aşamadaki bir diğer tip ise yine paranteze sahip olup variable bulundurmayan bir term: O halde parantezler doğrudan kaldırılabilir. Burada parantezler bizim için yalnızca işlem önceliği sağlar fakat yapılan tasarımda işlemin sonucu önem teşkil etmemektedir.
//Burada parantezler kaldırıldğında kalan işlemler kontrol edilir ve sonucunda da term'ün değişken tipine karar verilir.3 tipe sahip olabilir: Integer , String veya Error(String ve Integer'ın birlikte kullanılması veya içerisinde tanımlanmamış variable kullanımı olabilir.).
//4. aşamadaki bir term eğer kendi içerisinde parantez barındırmıyorsa: Bunu da yeniden ikiye ayırabiliriz: Variable içeren ve Variable içermeyen term.
//4. aşamadaki bir term parantessiz ve variable içeriyorsa: term içerisindeki variable ayrıştırılarak variable yokmuş gibi işlem yapılacak hale getirilir.
//Bu noktada variable olmadığında da term yeniden kendi içerisinde taranır ve 3 çeşit çıktıya sahip olabilir: String, Integer veya Error.
//5. Aşama ise specialkeyword ile başlama durumudur. Bu durumda dilimizin tanıdığı special keywordler belirlenmiş ve belirlenen keywordler üzerine çeşitli gruplar oluşturularak bazı koşullar yazılmıştır.

//Error 1:  Command Line is not open
//Error 2:  Command Line is not close 
//Error 3:  More than two consecutive operator is detected.
//Error 4:  The known operators are : ++, -- ,+,-,*,/,:=. The operand is not known by the Ceng Analyzer! --->
//Error 5:  A variable size cannot exceed twenty
//Error 6:  The number of digits that a number can have must be less than ten.
//Error 7:  Unknown character detected.
//Error 8:  String can not be null.
//Error 9:  Command Line is not finished.
//Error 10: Operand := expected.
//Error 11: Brackets are not correctly open or close.
//Error 12: The code can not start with endofline
//Error 13: The code must bu end with an end of line chracter (;).
//Error 14: The variable can use together with only three operator: := , ++ ,-- "
//Error 15: The operator must use with variable.
//Error 16: The operator must use with variable and variable must be Integer. 
//Error 17: The code can be start with an two operator: ++ , --.
//Error 18: Expression is not correctly design.
//Error 19: Expression include mismatch data type(s).
//Error 20: Unknown (or Object) data types can not be used in expression.
//Error 21: Variable declareted before int , it can not be redefined differant data type.
//Error 22: Special data types(long , char ... ) use with a variable name.
//Error 23: Special data types(long , char ... ) must be end with an endofline (;)

*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define FINISH -2
#define OPERATOR 1
#define LETTER 2
#define DIGIT 3
#define ENDOFLINE 4
#define BRACKET 5
#define UNKNOWN 6
#define STRING 7
#define INTEGER 8
#define VARIABLE 9
#define SPECIALKEYWORD 10
#define COMMENT 11
#define OBJECT 12

bool programFinish = false;
bool specialWordGroup1Flag = false;
bool returnStateController = false;
char input[4096];
int programCounter = 0;
char tempBuffer[30];
char currentChar;
int currentCharClass;
char str[1024];
int printCounter = 0;
char *errorMessage;

/////////////////////////////////////// GENERAL FUNCTIONS START \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/
//Bu struct yapısı kendi okuduğumuz değişkenlerin tiplerini(String,Integer,Object,Operator,...) ve içerisindeki veriyi korumak amacıyla yazılmıştır.
struct Object
{
    int itemClass;
    char data[1024];
};
//TwoArrayCopy aldığı source array'ini destiantion arrayine eşitleyerek source içerisinde bulunan tüm verilerin destination da da bulunmasını sağlar.

void TwoArrayCopy(struct Object *destination, struct Object *source, int l1)
{

    for (int i = 0; i < l1; i++)
    {
        destination[i] = source[i];
    }
    struct Object o;
    o.itemClass = FINISH;
    destination[l1] = o;
}
/////////////////////////////////////// GENERAL FUNCTIONS FINISH ////////////////////////////////////////

////////////////////////////////////// STORAGE OF PARSED VARIABLES START   \\\\\\\\\\\\\\\\\\\\\\\\\\\\\/
//Kod içerisindeki her karakteri okuyup türlerine karar verdikten sonra her türü içerisinde sakladığımız array.
struct Object analysisArray[2048];
int analysisArrayIndex = 0;
//Önceden tanımlanmış değişkenleri sakladığımız array
struct Object knownVariable[256];
int knownVariableIndex = 0;
//Belirlenmiş türlerin anaysisArray içerisine atmak için kullandığımız fonksiyon. Türünü ve verisini kendi içerisinde saklar
void addSyntaxArray(int itemC, char *var)
{
    //Gelen tür yaratılır ve bu türün tipini ve verisini aldığımız parametrelerle güncelliyoruz.
    struct Object o;
    o.itemClass = itemC;
    strcpy(o.data, var);
    analysisArray[analysisArrayIndex++] = o;
}
///////////////////////////////////// STORAGE OF PARSED VARIABLES FINISH   \\\\\\\\\\\\\\\\\\\\\\\\\\\\\/

///////////////////////////////////// FILE READ AND DELETE SPACES AND ETC. START  \\\\\\\\\\\\\\\\\\\\\\/

bool spaceFlag = true; // String değişkenlerinde boşlukları kaldırmamamız için bu flag ile kontrol sağlıyoruz
char *code;            // okuduğumuz değerlerin tutulduğu kısım
void read()
{
    FILE *file = fopen("code.Ceng", "r"); // dosyamız
    size_t n = 0;
    int c;
    if (file == NULL)
        return NULL; //could not open file
    code = malloc(1000);
    while ((c = fgetc(file)) != EOF)
    {
        if ((char)c == '"')
        {
            spaceFlag = !spaceFlag;
        }
        if (!spaceFlag)
        {
            code[n++] = tolower((char)c); // okurken case sensitive durumundan hepsini küçük yapıyoruz
        }
        else if ((char)c != '\n') // alt satıra inme ve tab boşlukları gibi özel karakterlerin olmadığı durumları eklememiz için
        {
            if ((char)c == '\r' || (char)c == '\t')
            {
                code[n++] = ' ';
            }
            else
            {
                code[n++] = tolower((char)c); // okurken case sensitive durumundan hepsini küçük yapıyoruz
            }
        }
    }
    code[n] = '\0'; // en son dosyanın bittiğini anlamamız için null ataması yapıyoruz
    // printf("%s", code);  // Okumanın doğruluğunu test etmek için yorum satırını kaldırın
}
//////////////////////////////////// FILE READ AND DELETE SPACES AND ETC. FINISH  \\\\\\\\\\\\\\\\\\\\\\/

//////////////////////////////////// BRACKET CHECK START  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/
static char bracketControlArray[256]; // bracker kontrolünü kontrol ederken stack mantığını kullanıyoruz bunun için de stack olarak bu arrayi tanımladık
static int bracketControlIndex = 0;   // buda stack pointerımız
bool bracketFlag = false;             // diğer özel durumlarda parantezlerin doğru yanlış dizilimlerini kontrol için bu değişkenler tutuldu
bool equalOperandFlag = false;
/// Burada standart stack yapısındaki pop push peek işlemleri bulunmakta
int pushBracket(char c)
{
    if (bracketControlIndex < 254)
    {
        bracketControlArray[bracketControlIndex++] = c;
        return 1;
    }
    return 0;
}
int popBracket()
{
    if (bracketControlIndex > 0)
    {
        bracketControlArray[bracketControlIndex--] = '\0';
        return 1;
    }
    return 0;
}
char peekBracket()
{
    return bracketControlArray[bracketControlIndex - 1];
}
int addBracket(char c) // bracket eklerken zaten bracketların eşleşip eşleşmediğini kontrol ediyoruz eğer 0 dönmesi durumunda hata vardır
{
    switch (c)
    {
    case '(':
        //printf("Left Round Bracket\n");
        return pushBracket(c);

    case ')':
        if (peekBracket() == '(')
        {
            //    printf("Right Round Bracket\n");
            return popBracket();
        }
        return 0;
    case '{':
        //  printf("Left Curly Bracket ");
        return pushBracket(c);
    case '}':
        if (peekBracket() == '{')
        {
            //     printf("Right Curly Bracket \n");
            return popBracket();
        }
        return 0;
    case '[':
        //  printf("Left Square bracket \n");
        return pushBracket(c);
    case ']':
        if (peekBracket() == '[')
        {
            //     printf("Right Square Bracket \n");
            return popBracket();
        }
        return 0;
    }
}

//////////////////////////////////// BRACKET CHECK FINISH \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/

////////////////////////////////////  COMMAND CONTROL CHECK  START   \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/
int openComment = 0;           // komut satırının açılması durumunda sayı bir artmakta bu sayede eğer açılma tagi == kapanma tagi diye kontrol ederek yorum satırını kontrol ediyoruz
int closeComment = 0;          // kapanma tagi sayacı
int checkCommandLine(char *ca) // komut satırında açılma ve kapanmalarının doğruluğunu kontrol ediyoruz.
{
    if (ca == "(*")
    {
        openComment++;
        return 1;
    }
    else
    {
        if (openComment > 0)
        {
            openComment--;
            return 1;
        }
        else
        {
            errorMessage = "Error 1: Command Line is not open , expected : (* !!! \n";
            return 0;
        }
    }
}
//////////////////////////////////// COMMAND CONTROL CHECK  FINISH \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/

///////////////////////////////    LEXICAL ANALYSES STARTS HERE  ///////////////////////////////////////
char getCurrentChar()
{ // okuduğumuz txtyi char by char olarak analiz ettiğimiz için
    if (code[programCounter] != '\0')
    {
        return code[programCounter++];
    }
    else
        return NULL;
}
int specialKeyword(char *str)
{
    ////////////////// Verilen dökümana göre special keyword ise 1 değilse 0 olarak döndürüyoruz.
    if (!strcmp(str, "break") ||
        !strcmp(str, "case") ||
        !strcmp(str, "char") ||
        !strcmp(str, "break") ||
        !strcmp(str, "const") ||
        !strcmp(str, "continue") ||
        !strcmp(str, "do") ||
        !strcmp(str, "else") ||
        !strcmp(str, "enum") ||
        !strcmp(str, "float") ||
        !strcmp(str, "for") ||
        !strcmp(str, "goto") ||
        !strcmp(str, "if") ||
        !strcmp(str, "int") ||
        !strcmp(str, "long") ||
        !strcmp(str, "record") ||
        !strcmp(str, "return") ||
        !strcmp(str, "static") ||
        !strcmp(str, "while"))
    {
        return 1;
    }
    return 0;
}
//Dosya içerisindeki her bir karakteri aldığımız fonksiyondur.
void getChar()
{
    //Eğer aldığımız karakter null değilse tipini bulmaya çalışıyoruz.
    if ((currentChar = getCurrentChar()) != NULL)
    {
        //Aşağıda gösterilen operatörlerden biri ise matematiksel operator olabilir veya atama operatörü olabilir comment line olabilir veya hatalı bir yazıma sahip olabilir.
        if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/' || currentChar == ':' || currentChar == '=')
        {
            //Eğer comment line ise --> *)
            if ((currentChar == '*' && code[programCounter] == ')'))
            {
                if (checkCommandLine("*)"))
                {
                    currentChar = getCurrentChar();
                    currentCharClass = COMMENT;
                }
                else //Comment line hatalı girildiyse
                {
                    errorMessage = "Error 2: Command Line is not close , expected : *) ! \n";
                    currentChar = '\0';
                    currentCharClass = FINISH;
                }
            }
            else //Eğer comment line değilse ve := buna eşit ise hatalı durumları ile birlikte kontrol ediyoruz.
            {
                if (currentChar == ':' && code[programCounter] != '=')
                {
                    equalOperandFlag = true;
                    currentCharClass = FINISH;
                }
                else if (currentChar == '=' && code[programCounter - 2] != ':')
                {
                    equalOperandFlag = true;

                    currentCharClass = FINISH;
                }
                else
                {
                    equalOperandFlag = false;
                    currentCharClass = OPERATOR;
                }
            }
        }
        //String olması durumu
        else if (currentChar == '"')
        {
            currentCharClass = STRING;
        }
        //Bir karakter olup alfabade bulunup bulunmadığını kontrol ediyoruz.Eğer doğruysa harftir.
        else if (isalpha(currentChar))
        {
            currentCharClass = LETTER;
        }
        //Bitiş işareti
        else if (currentChar == ';')
        {
            currentCharClass = ENDOFLINE;
        }
        //Rakamlardan biri midir bunu kontrol ediyoruz.Eğer doğruysa rakamdır
        else if (isdigit(currentChar))
        {
            currentCharClass = DIGIT;
        }
        //Eğer bracket ise
        else if (currentChar == '(' || currentChar == '{' || currentChar == '[' || currentChar == ')' || currentChar == '}' || currentChar == ']')
        {
            //Comment line olarak girilmiş olabilir --> (*
            if (currentChar == '(' && code[programCounter] == '*')
            {
                checkCommandLine("(*");
                currentCharClass = COMMENT;
                currentChar = getCurrentChar();
            }
            else //Diğer durumda bir stack aracılığıyla bracketların doğruluğu kontrol edilir. Eğer bracket sayıları ve yapıları doğruysa bracket olarak döner diğer durumda hata mesajı göndeilir.
            {
                bracketFlag = false;
                if (addBracket(currentChar))
                {
                    currentCharClass = BRACKET;
                }
                else
                {
                    bracketFlag = true;
                    currentCharClass = FINISH;
                }
            }
        }
        //Bilinmeyen durumlardır.
        else
        {
            currentCharClass = UNKNOWN;
        }
    }
    //Kodun tamamen bitmesi durumudur.
    else
    {
        currentCharClass = FINISH;
    }
}
int bufCounter = 0; // verilen koşulların (örneğin integer 10 digit , variable 20 karakter olur gibi şeylerdeki uzunluğu analiz etmemiz için bu sayaç var)
void addBuffer()
{ /// Okuduğumuz ve analiz ettiğimiz kısımdakilerin toplu olarak gösterimi için bir buffera eklenmekte
    if (currentChar != '"')
    {
        tempBuffer[bufCounter++] = currentChar;
        if (bufCounter < 30)
        {
            tempBuffer[bufCounter] = '\0';
        }
    }
}
int lexicalAnalyser() // lexial analizi yaptığımız fonsiyon
{
    bufCounter = 0;
    int strCounter = 0;
    switch (currentCharClass) //okunan char'ın  hangi classta olduğunu  swich-case ile kontrol ediyoruz
    {
    case OPERATOR:                           //okunan char OPERATOR ise bu case çalışıyor
        addBuffer();                         // okunan char'ı addBuffer ile bir arrayde topluyoruz
        getChar();                           //bir sonraki char değerini okuyoruz
        while (currentCharClass == OPERATOR) //sonrasında okunan değerin classı OPERATOR olduğu sürece addBuffer fonsiyonunu çağırıp arraya char'ı ekliyoruz.
        {
            addBuffer();
            if (bufCounter > 2) //Operatorler ikiden fazla yanyana gelemez. İkiyi grçmesi durumunda hata mesajı veriyoruz.
            {

                errorMessage = "Error 3: The known operators are : ++, -- ,+,-,*,/,:=. The operand is not known by the Ceng Analyzer! --> \nMore than two consecutive operator is detected.\n";
                return FINISH;
            }
            getChar();
        }
        //yanyana gelen operator sayısı iki ise bunlar sadece ++ -- veya := olabilir.Bunun haricinde herhangi iki opeartor yanyana gelirse hata mesajı veriyoruz.
        if (strcmp(tempBuffer, "++") && strcmp(tempBuffer, "--") && strcmp(tempBuffer, ":=") && bufCounter == 2)
        {

            errorMessage = "Error 4: The known operators are : ++, -- ,+,-,*,/,:=. The operand is not known by the Ceng Analyzer! --->\n";

            return FINISH;
        }
        addSyntaxArray(OPERATOR, tempBuffer); //Syntax fonsiyonunda kullanmak için okunan değerin classını ve değerini addSyntaxArray adını verdiğimiz bir fonsiyon yardımıyla bir struct arrayında topluyoruz.
        return OPERATOR;
    case LETTER:     //okunan char LETTER ise bu case çalışıyor
        addBuffer(); // okunan char'ı addBuffer ile bir arrayde topluyoruz
        getChar();   //bir sonraki char değerini okuyoruz
        // Okunan char letter ise bu variable olacağından içerisinde sayı veya _ karakteri bulunabilir. Bunda dolayı okunan char'ın classının LETTER DIGIT veya değerinin _ olması durumdan döngü devam eder ve charlar arrayde tolanır
        while (currentCharClass == LETTER || currentCharClass == DIGIT || currentChar == '_')
        {
            addBuffer();
            //variable uzunluğu 20den fazla olamaz.20'yi geçmesi durumunda hata mesajı veriyoruz.
            if (bufCounter > 20)
            {
                errorMessage = "Error 5: A variable size cannot exceed twenty \n";
                return FINISH;
            }
            getChar();
        }
        //Arrayde toplanan değeri specialKeyword adını verdiğimiz fonsiyonda speacial keyword olup olmamadığını kontrol ediyoruz.
        if (specialKeyword(tempBuffer))
        {
            //Eger okunan değer special keyword ise classı SPECIALKEYWORD olarak addSyntaxArray fonsiyonuna gönderiliyor.
            addSyntaxArray(SPECIALKEYWORD, tempBuffer);
            return SPECIALKEYWORD;
        }
        //Eger okunan değer variable ise classı VARIABLE olarak addSyntaxArray fonsiyonuna gönderiliyor.
        addSyntaxArray(VARIABLE, tempBuffer);
        return VARIABLE;

    case DIGIT:                           //okunan char DIGIT ise bu case çalışıyor
        addBuffer();                      // okunan char'ı addBuffer ile bir arrayde topluyoruz
        getChar();                        //bir sonraki char değerini okuyoruz
        while (currentCharClass == DIGIT) //sonrasında okunan değerin classı DIGIT olduğu sürece addBuffer fonsiyonunu çağırıp arraya char'ı ekliyoruz.
        {
            addBuffer();
            //digit sayısı 10 basamaktan fazla olamaz.Eğer 10dan fazla olursa hata mesajı veriyoruz.
            if (bufCounter > 10)
            {
                errorMessage = "Error 6: The number of digits that a number can have must be less than ten. \n";
                return FINISH;
            }
            getChar();
        }
        addSyntaxArray(INTEGER, tempBuffer); //Syntax fonsiyonunda kullanmak için okunan değerin classını ve değerini addSyntaxArray adını verdiğimiz bir fonsiyon yardımıyla bir struct arrayında topluyoruz.
        return INTEGER;
    case ENDOFLINE:  //okunan char ENDOFLİNE ise bu case çalışıyor
        addBuffer(); // okunan char'ı addBuffer ile bir arrayde topluyoruz
        getChar();   //bir sonraki char değerini okuyoruz
        ///////////////////// BURADA SYNTAX ANALİZİ VAR //////////////////////////////////////////
        addSyntaxArray(ENDOFLINE, tempBuffer); //Syntax fonsiyonunda kullanmak için okunan değerin classını ve değerini addSyntaxArray adını verdiğimiz bir fonsiyon yardımıyla bir struct arrayında topluyoruz.
        ///////////////////// BURADA SYNTAX ANALİZİ BİTİYOR //////////////////////////////////////////
        return ENDOFLINE;
    case BRACKET:                            //okunan char BRACKET ise bu case çalışıyor
        addBuffer();                         // okunan char'ı addBuffer ile bir arrayde topluyoruz
        getChar();                           //bir sonraki char değerini okuyoruz
        addSyntaxArray(BRACKET, tempBuffer); //Syntax fonsiyonunda kullanmak için okunan değerin classını ve değerini addSyntaxArray adını verdiğimiz bir fonsiyon yardımıyla bir struct arrayında topluyoruz.
        return BRACKET;
    case UNKNOWN:               //okunan char UNKNOWN ise bu case çalışıyor
        if (currentChar == ' ') //Boşluk karakterinin tanınmadığı için UNKNOWN olarak tanımlanıyor.
        {
            getChar();
            while (currentChar == ' ') //okunan char boşluk olduğu sürece tekrar okuyoruz ve boşlıkları geçmiş oluyoruz.
            {
                getChar();
            }
            return UNKNOWN;
        }
        else //Diğer tüm bilinmeyen karakterler için hata mesajı yazıyoruz.
        {
            errorMessage = "Error 7: Unknown character detected. \n";
            return FINISH;
        }
    case STRING:                                          //okunan char tırnak işareti ise (") ise bu case çalışıyor.
        getChar();                                        //bir sonraki char değerini okuyoruz
        while (currentChar != '"' && currentChar != '\0') // okunan değer tekrar tırnak işareti ve \0 olmadığı sürece getchar fonsiyonu çalışıyor ve okunan char str arrayında toplanıyor.
        {
            str[strCounter++] = currentChar;
            getChar();
        }
        str[strCounter] = '\0';  //en sona '/0' ekliyoruz
        if (currentChar == '\0') // currentChar null ise hata mesajı yazdırıyoruz.
        {
            errorMessage = "Error 8: String can not be null. \n";
            return FINISH;
        }
        getChar();
        addSyntaxArray(STRING, str); //Syntax fonsiyonunda kullanmak için okunan değerin classını ve değerini addSyntaxArray adını verdiğimiz bir fonsiyon yardımıyla bir struct arrayında topluyoruz.
        return STRING;
    case COMMENT: //okunan char (* ise bu case çalışıyor.
        addBuffer();
        getChar();
        while (currentCharClass != COMMENT && currentChar != '\0') // *) işareti gelene veya okunan değer null olana kadar içerisindeki değerler yorum satırı olarak algılıyoruz ve geçiyoruz
        {
            addBuffer();
            getChar();
        }
        addBuffer();
        getChar();
        if (currentChar == '\0') // currentChar null ise hata mesajı yazdırıyoruz.
        {
            errorMessage = "Error 9: Command Line is not finished , expected ';' \n";
            return FINISH;
        }
        return COMMENT;
    case FINISH:              //okunan char hiçbir durumu sağlamadığında classı FINISH olarak algılanıyor .
        if (equalOperandFlag) //eğer := ifadesi olmayan durumlarda hata vermesi için
        {
            errorMessage = "Error 10: Operand := expected. \n";
            return FINISH;
        }
        if (bracketControlIndex > 0 || bracketFlag) //parantezin açılıp kapanmasında bir hata varsa hata mesajı veriyoruz.
        {
            errorMessage = "Error 11: Brackets are not correctly open or close. \n";
            return FINISH;
        }
        addSyntaxArray(-2, "FINISH"); //Programımız lexical analizden başarıyla geçerse syntax analizi için bunu ekliyoruz.
        programFinish = true;         //Syntax analizine girmesi için true yapıyoruz.
        return FINISH;
    }
}
///////////////////////////////    LEXICAL ANALYSES FINISH HERE  /////////////////////////////////////////

//////////////////////////////     SYNTAX ANALYSES START HERE ///////////////////////////////
int pushVariable(struct Object o) // Kodu analiz ederken syntax olarak var:45; gibi değeri analiz ettiğimizde altta var'ın bir ifadede kullanılmasını ve türünü tutmak için buraya ekliyoruz
{
    if (knownVariableIndex < 254)
    {
        knownVariable[knownVariableIndex++] = o;
        return 1;
    }
    return 0;
}
int searchVariable(char *param) // variable ile karşılaştığımda daha önce geçti mi geçmedi mi değeri türü ne onu bulduruyorum
{
    //return 7 ise string
    //return 8 ise integer
    //return 12 ise Object
    //return 0 ise bulunamadı
    for (int i = 0; i < knownVariableIndex; i++)
    {
        if (!strcmp(knownVariable[i].data, param))
        {
            return knownVariable[i].itemClass;
        }
    }
    return 0;
}
int nextLineAnalysisIndex = 0;
bool bracketExp = false;   // specialkeyword parantazlerini var:= ... ; daki atama parantezlerinden ayırmayı kontrol etmek için tuttuğumuz değişken
int controlBrackets(int m) /// var :=  .... ; ya da var := .... kısmında ... içerisinde parantez var mı yok mu kontrol ediyorum
{
    bracketExp = false; // special keywordlerdeki parantezler ile var:= ... ; daki kullanılacak parantezlerin karışmamasını sağlayan flag
    for (int i = m; i < analysisArrayIndex; i++)
    {
        if (specialWordGroup1Flag)
        {
            if (analysisArray[i + 1].itemClass == BRACKET && !strcmp(analysisArray[i + 1].data, "{"))
            {
                nextLineAnalysisIndex = i; // burada var:= .........; ; kısmı hangi indexte bitiyor onu güncelliyorum!!!!! BURASI AŞAĞIDAKİ ANALİZLERDEKİ nextLineAnalysisIndexi Kontrol etmek için önemli
                specialWordGroup1Flag = false;
                break;
            }
        }
        if (analysisArray[i].itemClass == ENDOFLINE || analysisArray[i].itemClass == FINISH)
        {
            nextLineAnalysisIndex = i; ///////// burada var:= .........; ; kısmı hangi indexte bitiyor onu güncelliyorum!!!!! BURASI AŞAĞIDAKİ ANALİZLERDEKİ nextLineAnalysisIndexi Kontrol etmek için önemli
            break;
        }
        if (analysisArray[i].itemClass == BRACKET && !(strcmp(analysisArray[i].data, ")") && strcmp(analysisArray[i].data, "("))) //var ın yanındaki kısımda sadece ) veya ( bu olabilir.
        {
            bracketExp = true;
        }
        if (analysisArray[i].itemClass == BRACKET && (strcmp(analysisArray[i].data, ")") && strcmp(analysisArray[i].data, "("))) //var ın yanındaki kısımda sadece ) veya ( bu olabilir.
        {
            return -1;
        }
    }
    if (bracketExp)
    {
        return 1;
    }
    return 0;
}
int expressionBracketsCalculator(int start, int finish)
{
    // var:= ............ ; (var++) (++var+5)
    /// Bu fonksiyonda parantez içlerindeki var++ gibi değerlerin yerine doğrudan integer yazıyoruz eğer bunu yapmaz isek parantezler kalktığında operant hatası verir !!
    struct Object checkList[512]; /// Yeniden oluşturacağımız için (var++) yerine int yazacağımız için bir array tanımlıyoruz
    int cI = 0;                   // bu arraye parantezleri ekleyemiyeceğimiz için eklerkenki indexi özel olarak tutuyoruz

    for (int i = start; i < finish; i++)
    {
        /// --var ise
        if (analysisArray[i].itemClass == OPERATOR && !(strcmp(analysisArray[i].data, "++") && strcmp(analysisArray[i].data, "--")) && analysisArray[i + 1].itemClass == VARIABLE && searchVariable(analysisArray[i + 1].data) == INTEGER)
        {
            struct Object o;
            o.itemClass = INTEGER;
            strcpy(o.data, analysisArray[i + 1].data);
            checkList[cI++] = o;
            i = i + 1;
        }
        // var++ örneğin
        else if (analysisArray[i].itemClass == VARIABLE && searchVariable(analysisArray[i].data) == INTEGER && !(strcmp(analysisArray[i + 1].data, "++") && strcmp(analysisArray[i + 1].data, "--")))
        {
            struct Object o;
            o.itemClass = INTEGER;
            strcpy(o.data, analysisArray[i].data);
            checkList[cI++] = o;
            i = i + 1;
        }
        else
        {
            checkList[cI++] = analysisArray[i];
        }
    }
    /// Şuan elimizdeki varların ++ veya -- olması durumundan kurtulduk
    struct Object newItems[512];
    int secondIndex = 0;
    for (int i = 0; i < cI; i++)
    {
        if (checkList[i].itemClass != BRACKET)
        {
            newItems[secondIndex++] = checkList[i];
        }
    }
    struct Object backUp[2048];
    TwoArrayCopy(backUp, analysisArray, 2047);
    TwoArrayCopy(analysisArray, newItems, secondIndex);
    int res = expressionCalculator(newItems[0].itemClass, 0, secondIndex);
    if (res)
    {
        TwoArrayCopy(analysisArray, backUp, 2047);
        return 1;
    }
    return 0;
}
int controlVariable(int start, int finish) /// var := ..... ; .... içerisinde variable var mı yok mu onu kontrol ediyoruz parse treemiz için gerekli
{
    for (int i = start; i < finish; i++)
    {
        if (analysisArray[i].itemClass == VARIABLE)
        {
            return 1;
        }
    }
    return 0;
}
//Bir term kendi içerisinde doğru tiplerle mi işlem yapıyor kontrol ediyoruz.
int expressionCalculator(int firstVariableType, int startIndex, int FinishIndex)
{
    //Operatör variable integer string mi kotnrolü için gerekli olan değişkenimiz.
    int j = 0;
    if (firstVariableType == STRING) // eğer var:= str....; diye gidiyor ise aradaki operatorler sadece + olabilir ve değişken de varsa onun tipi sadece string olabilir
    {
        for (int i = startIndex; i < FinishIndex; i++)
        {
            if (j % 2 == 0 && (analysisArray[i].itemClass != STRING || (analysisArray[i].itemClass == VARIABLE && searchVariable(analysisArray[i].data) == STRING)))
            {
                return 0;
            }
            else if (j % 2 == 1 && strcmp(analysisArray[i].data, "+"))
            {
                return 0;
            }
            j++;
        }
        /////Burada o variablenin analizinde bir sorun yok ise ve analiz doğru ise o değişken var:= .. ; doğru tanımlanmıştır ve bilinen değişkenlere eklenir.
        struct Object o = analysisArray[startIndex - 2];
        o.itemClass = STRING;
        pushVariable(o);
        return 1;
    }
    else if (firstVariableType == INTEGER)
    {
        //burada j çift sayı ise biliyorum ki bir variable veya integer değişken olmalıdır. eğer tek sayı ise operatör olmalıdır.
        for (int i = startIndex; i < FinishIndex; i++)
        {
            //eğer çift sayıysa j ve operatör harici bir şeyse hata vermelidir.
            if (j % 2 == 0 && (analysisArray[i].itemClass != INTEGER && analysisArray[i].itemClass != VARIABLE))
            {
                return 0;
            }
            //// eğer var:= int....; diye gidiyorsa ben biliyorum ki benim variable değişkenimin tipi mutlaka integer olmalıdır.
            if (j % 2 == 0 && analysisArray[i].itemClass == VARIABLE && searchVariable(analysisArray[i].data) != INTEGER)
            {
                return 0;
            }
            //Aşağıda belirtilen operatörler harici herhangi başka bir operatör bulunamaz.
            else if (j % 2 == 1 && strcmp(analysisArray[i].data, "+") && strcmp(analysisArray[i].data, "-") && strcmp(analysisArray[i].data, "*") && strcmp(analysisArray[i].data, "/"))
            {
                return 0;
            }
            //++ ve -- durumun var ise variableın türüne bakılmaktadır.
            else if (j % 2 == 1 && !(strcmp(analysisArray[i].data, "++") || !strcmp(analysisArray[i].data, "--")) && (searchVariable(analysisArray[i - 1].data) != INTEGER || analysisArray[i + 1].itemClass != ENDOFLINE))
            {
                return 0;
            }
            j++;
        }
        /////Burada o variablenin analizinde bir sorun yok ise ve analiz doğru ise o değişken var:= .. ; doğru tanımlanmıştır ve bilinen değişkenlere eklenir.
        struct Object o = analysisArray[startIndex - 2];
        o.itemClass = INTEGER;
        pushVariable(o);
        return 1;
    }
    //Eğer integer ve string harici her hangi bir değişken term içerisinde bulunuyorsa hata veriyoruz.
    else if (firstVariableType != INTEGER && firstVariableType != STRING)
    {
        return 0;
    }
}

int specialWordGetGroup(char *param) // Special keywordleri bu şekilde kurallarına göre pars edeceğimiz için hangi grupta olduğunu buldurduğumuz kısım
{
    /*
    Grup 1:
        if(){}
        while(){}
        for(){}
    Grup 2:
        break;
        goto;
        continue;
    Grup 3:
        int varName;
        long varName
        record varName
        char varName; 
        float varName;
        enum varName;
        const  varName;
        static varName;
    Group 4:
        return varName;
        return int | string;
    Group 5: 
        do ()
        else()
    Non Group 6:
        case;
    */
    if (!strcmp(param, "if") || !strcmp(param, "while") || !strcmp(param, "for"))
    {
        return 1;
    }
    else if (!strcmp(param, "break") || !strcmp(param, "goto") || !strcmp(param, "continue"))
    {
        return 2;
    }

    else if (!strcmp(param, "int") || !strcmp(param, "long") || !strcmp(param, "record") || !strcmp(param, "char") || !strcmp(param, "float") || !strcmp(param, "enum") || !strcmp(param, "const") || !strcmp(param, "static"))
    {
        return 3;
    }
    else if (!strcmp(param, "return"))
    {
        return 4;
    }
    else if (!strcmp(param, "do") || !strcmp(param, "else"))
    {
        return 5;
    }
    else
    {
        return 6;
    }
}

char *getBracketNamet(char c) // bracket eklerken zaten bracketların eşleşip eşleşmediğini kontrol ediyoruz eğer 0 dönmesi durumunda hata vardır
{
    switch (c)
    {
    case '(':
        return "Left Round Bracket\n";
    case ')':
        return "Right Round Bracket\n";
    case '{':
        return "Left Curly Bracket\n";
    case '}':
        return "Right Curly Bracket \n";
    case '[':
        return "Left Square Bracket \n";
    case ']':
        return "Right Square Bracket \n";
    }
}

int checkSyntax()
{
    //Lexical anayze fonksiyonunda Belirlenmiş olan arrayin tüm lengthini bulduğumuz kısım.
    int lenghtofAll = sizeof(analysisArray) / sizeof(analysisArray[0]);
    //Analyze index içerisinde bulunan her bir türü alıyoruz ve belirlenen fonksiyonlar arıcışığıyla kontrol ediyoruz.
    for (int i = 0; i < lenghtofAll; i++)
    {
        printCounter = i;
        //Kodun tamamen bitmesi durumu burada yazılmıştır hem syntax hem de lexical olarak doğru bir şekilde analiz edilmiştir.
        if (!strcmp(analysisArray[i].data, "FINISH"))
        {
            break;
        }
        /////////////////////////////////////////// Kodumuzun başlayabileceği durumlar: ++var,var++,var; var:=, spec ///////////////////////////////////
        //!!!!!!!!!!!!!!!!!!!!!!eğer kodun en başıysa veya } bunun yanındaysa veya ; bunun yanındaysa en başta sayılabilir.

        int previusItemClass = analysisArray[i - 1].itemClass;
        int currentItemClass = analysisArray[i].itemClass;
        int nextItemClass = analysisArray[i + 1].itemClass;

        /////////////////////////////////////////// BELİRTİLEN BAŞLANGIÇLARIN KONTROLÜ: ++var,var++,var;  BURADA BAŞLIYOR ///////////////////////////////////
        //Kodun veya satırın başlangıcıysa anlamına gelmektedir.
        if (i == 0 || (i > 0 && (previusItemClass == ENDOFLINE || !strcmp(analysisArray[i - 1].data, "}"))))
        {
            //var; -> Böyle bir durumda variable object kabul edilerek knownvariable içerisine eklenmektedir.
            if (currentItemClass == VARIABLE && nextItemClass == ENDOFLINE)
            {
                struct Object o;
                o = analysisArray[i];
                o.itemClass = OBJECT;
                pushVariable(o);
                i = i + 1;
            }
            //Eğer special bir keyword yok veya variable ile başlamıyorsa yine de endofline var ise hata vermelidir.
            if (currentItemClass != SPECIALKEYWORD && currentItemClass != VARIABLE && nextItemClass == ENDOFLINE)
            {
                errorMessage = "Error 12: The code can not start with endofline \n";
                return 0;
            }
            //variable ile başlıyor sonrasında operatör gelmiş ve bu operatör eğer := ise ve sonunda endofline bulunmuyorsa hata vermelidir.
            else if (currentItemClass == VARIABLE && nextItemClass == OPERATOR && strcmp(analysisArray[i + 1].data, ":=") && analysisArray[i + 2].itemClass != ENDOFLINE)
            {
                errorMessage = "Error 13: The code must bu end with an end of line chracter (;). \n";
                return 0;
            }
            //variable ile başlamış ve sonraki opratörler: := , ++ , -- bunlardan farklı ise hata vermelidir.
            else if (currentItemClass == VARIABLE && nextItemClass == OPERATOR && strcmp(analysisArray[i + 1].data, ":=") && analysisArray[i + 2].itemClass == ENDOFLINE && strcmp(analysisArray[i + 1].data, "++") && strcmp(analysisArray[i + 1].data, "--"))
            {
                errorMessage = "Error 14: The variable can use together with only three operator: := , ++ ,-- \n";
                return 0;
            }
            //Eğer şuanda operatör ise ve yanıdnda variable harici bir şey bulunuyorsa hatalıdır.
            else if (currentItemClass == OPERATOR && nextItemClass != VARIABLE)
            {
                errorMessage = "Error 15: The operator must use with variable. \n";
                return 0;
            }
            //Eğer operatör ile başlamış varibale olmasına rağmen tipi integer harici bir değişken ise hata vermektedir.
            else if (currentItemClass == OPERATOR && nextItemClass == VARIABLE && searchVariable(analysisArray[i + 1].data) != INTEGER)
            {
                errorMessage = "Error 16: The operator must use with variable and variable must be Integer. \n";
                return 0;
            }
            //Operatör ile başlamış ve variable doğru gelmiş end of line ile bitmemiş ise hata vermelidir.
            else if (currentItemClass == OPERATOR && nextItemClass == VARIABLE && searchVariable(analysisArray[i + 1].data) == INTEGER && analysisArray[i + 2].itemClass != ENDOFLINE)
            {
                errorMessage = "Error 13: The code must bu end with an end of line chracter (;). \n";
                return 0;
            }
            //operatör ile başlamış ve variable doğru ise endofline ile bitmişse ama operatörler ++ veya -- den farklı ise hata vermelidir.
            else if (currentItemClass == OPERATOR && nextItemClass == VARIABLE && searchVariable(analysisArray[i + 1].data) == INTEGER && analysisArray[i + 2].itemClass == ENDOFLINE && strcmp(analysisArray[i].data, "++") && strcmp(analysisArray[i].data, "--"))
            {
                errorMessage = "Error 17: The code can be start with an two operator: ++ , --. \n";
                return 0;
            }
        }
        /////////////////////////////////////////// BELİRTİLEN BAŞLANGIÇLARIN KONTROLÜ: ++var,var++,var;  BURADA BİTİYOR ///////////////////////////////////

        // var=; için yapılan kontrolleri içeriyor. variable önüne int special key word alabilir. Bu if bloğu bunu da kontrol ediyor.specialWordGroup1Flag , returnStateController flaglerini ise returnden sonra gelen veya if for veya while yapısının parantezi içerisindeki yazımın doğruluğunu kontrol etmek için kullanıyoruz.
        if (specialWordGroup1Flag || returnStateController || (currentItemClass == VARIABLE && !strcmp(analysisArray[i + 1].data, ":=") && (i == 0 || (i > 0 && (previusItemClass == ENDOFLINE || !strcmp(analysisArray[i - 1].data, "int") || !strcmp(analysisArray[i - 1].data, "}"))))))
        {
            int lineStart = i + 2;                    /// var:= dan sonra ki ilk gelen charın indexini lineStart değişkeninde saklıyoruz.
            int phranthases = controlBrackets(i + 2); /// var:= den sonra gelen ilk kısımdan itibaren ENDOFLINE görene kadar parantez olup olmadığı kontrol ediliyor ve ENDOFLINE görülen yerin indexi nextLineAnalysis ile tutuluyor.
            if (phranthases == -1)                    // parantez kontrolü yaparken eğer hatalı bir durum varsa -1 dönüyoruz  bu durumda  hata mesajı yazıyoruz.
            {
                errorMessage = "Error 11: Brackets are not correctly open or close. \n";
                return 0;
            }
            if (phranthases) // var := den sonra parantez var ise  1 dönüyoruz ve bu if bloğu çalışıyor.
            {
                int isThereVariable = controlVariable(lineStart, nextLineAnalysisIndex); // var := den sonra ,yani lineStart ve nextLineAnalysisIndex arasında variable var ise 1 yok ise 0 dönüyoruz.
                if (isThereVariable)                                                     // Eğer parantez var ise bu if bloğu çalışıyor
                {
                    int res = expressionBracketsCalculator(lineStart, nextLineAnalysisIndex); // Variableların türlerinin kontrollerinin yapıldığı ve tüm parantezlerin kontrollerinin yapıldığı fonsiyondur.Eğerki işlem içerisinde aynı türde olmayan variableler veya farklı bir türler arası işem var ise 0 dönüyoruz. Yok ise doğru kbul edip 1 dönüyoruz.
                    if (res != 1)                                                             //0 dönmüş ise hatalıdır. Hata mesajı yazıyoruz.
                    {
                        errorMessage = "Error 18: Expression is not correctly design.  \n";
                        return 0;
                    }

                    i = nextLineAnalysisIndex; // ENDOFLİNE a kadar kontrol edildiği için gelinen indexi i'ye eşitliyoruz.
                }
                else //Eğer variable içermiyorsa else bloğu çalışıyor.
                {    // Parantezli ve variablesız yapılar olduğu için parantezleri kaldırarak kontrolleri yapıyoruz
                    struct Object backup[2048];
                    TwoArrayCopy(backup, analysisArray, 2047); // Parantezleri kadırmadan önce tüm yapıların içinde bulunduğu analysisArray'ın yedeğini alıyoruz.
                    struct Object newItems[512];               // parantezlerin kaldırılmış halini newItems arrayi içerisinde topluyoruz.
                    int f = 0;
                    for (int k = lineStart; k < nextLineAnalysisIndex; k++) //Parantezlerin kaldırılarak newItems içerisinde toplandığı kısım.
                    {

                        if (analysisArray[k].itemClass != BRACKET) // bracketları kaldırıyorum var:= ..... ; / ... olan yerdeki bracketları kaldırdım
                        {
                            newItems[f] = analysisArray[k];
                            f = f + 1;
                        }
                    }
                    TwoArrayCopy(analysisArray, newItems, 511);              //Parantezleri kaldırılmış halini tutan arrayı analysisArray'a kopyalıyoruz.
                    int firstVariableType = analysisArray[2].itemClass;      // var := sonra gelen ilk yapının hangi classta olduğunu firstVariableType adındaki değşkende tutuyoruz.
                    int res = expressionCalculator(firstVariableType, 2, f); // Bu fonksiyon ile var := sonraki işlemlerin tamamının aynı türler arasında yapılıp yapılmadığını kontrol ediyoruz eğer ayrı türler arasında yapılan bir işlem var ise ( örneğin "aa"+2) 0 dönüyoruz.Eğer hata yok ise 1 dönüyoruz.
                    if (res)                                                 // eğer dönen değer 1 ise hata yoktur
                    {
                        i = nextLineAnalysisIndex; // var:= .... ; ... kısmını analiz ettiğim için atlıyorum ve endoflinın olduğu yere geldim
                    }
                    else // 0 dönüyorsa hata vardır ve hata mesajı yazıyoruz.
                    {
                        errorMessage = "Error 19: Expression include mismatch data type(s). \n";
                        return 0;
                    }
                    TwoArrayCopy(analysisArray, backup, 2047); // Yukarıda analsisArrayin tamamını backup arrayına kopyalayıp saklamıştık.İşlemler bittikten sonra tekrar AlaysisArraya geri kopyalıyoruz.
                }
            }
            else /// var:= yapısından sonra ENDOFLİNE a kadar parantez yok ise else bloğu çalışıyor.
            {
                int isThereVariable = 0;
                isThereVariable = controlVariable(lineStart, nextLineAnalysisIndex); // var:= yapısından sonra variable içerip içermediğini kontrol ediyoruz.

                if (analysisArray[nextLineAnalysisIndex].itemClass == FINISH) // eğer var :=; şeklinde bir yapı varsa hatalı bir yazımdır.Hata mesajı veriyoruz.
                {
                    errorMessage = "Error 13: The code must bu end with an end of line chracter (;). \n";
                    return 0;
                }

                if (isThereVariable) // Eğer variable var ise if bloğu çalışıyor.
                {
                    int firstVariableType;
                    if (analysisArray[lineStart].itemClass == VARIABLE) // Eğer var:= sonra gelen ilk yapı variable ise  bu variable'ın classını (Satring variable mı integer variable mı object variable mı yoksa hiçbir bilgi yok mu) konrol ediyoruz.
                    {
                        firstVariableType = searchVariable(analysisArray[lineStart].data);
                        if (firstVariableType == OBJECT || firstVariableType == 0) //Eğer object ise veya classı belli değise herhangi bir işeme dahil olamayacağından hata mesajı yazıyoruz.
                        {
                            errorMessage = "Error 20: Unknown (or Object) data types can not be used in expression. \n";
                            return 0;
                        }
                    }
                    else //eğer var:= sonra gelen ilk yapı variable değilse else bloğu çalışıyor.
                    {
                        firstVariableType = analysisArray[lineStart].itemClass; // Bu yapının hangi classta olduğunu kontrol ediyoruz.
                    }
                    int res = expressionCalculator(firstVariableType, lineStart, nextLineAnalysisIndex); // var := den sonra gelen ilk yapının classı bilindikten sonra işleme dahil olan yapıların tamamının aynı classtan olup olmadığını kontrol ediyoruz.
                    if (res)                                                                             //eğer hepsi aynı tür ise 1 herhangi bir hata yoktur.
                    {
                        i = nextLineAnalysisIndex; // tekrardan var:= ... ; ... kısmını atlatıyorum
                    }
                    else //Eğer 0 döner ise farklı türler arası işlem yapılmaya çalışıldığı anlaşılacağından hata mesajı yazıyoruz.
                    {
                        errorMessage = "Error 19: Expression include mismatch data type(s). \n";
                        return 0;
                    }
                }
                else // Eğer var:= yapısı parantez ve variable içermiyorsa else bloğu çalışır.
                {
                    int firstVariableType = analysisArray[lineStart].itemClass;                                       // var := sonra gelen ilk yapının hangi classta olduğunu belirliyoruz.
                    if (searchVariable(analysisArray[lineStart - 2].data) == INTEGER && firstVariableType != INTEGER) //Eğer içine atama yapacağımız variable (var := şeklinde belirttiğimiz kısım) ineteger bir variable ise := yapısından sonra gelen yapıda integer olmak zorunda .Eğer integer olan bir variable'a farklı türden bir atama yapılıyorsa hata verir.
                    {
                        errorMessage = "Error 21: Variable declareted before int , it can not be redefined differant data type . \n";
                        return 0;
                    }
                    int res = expressionCalculator(firstVariableType, lineStart, nextLineAnalysisIndex); //  var := den sonra gelen ilk yapının classı bilindikten sonra işleme dahil olan yapıların tamamının aynı classtan olup olmadığını kontrol ediyoruz.
                    if (res)                                                                             //eğer hepsi aynı tür ise 1 herhangi bir hata yoktur.
                    {
                        i = nextLineAnalysisIndex; // tekrardan var:= ... ; ... kısmını atlatıyorum
                    }
                    else //Eğer 0 döner ise farklı türler arası işlem yapılmaya çalışıldığı anlaşılacağından hata mesajı yazıyoruz.
                    {
                        errorMessage = "Error 19: Expression include mismatch data type(s). \n";
                        return 0;
                    }
                }
            }
        }
        returnStateController = false;
        //öncelikle yeni bir satırın başlaması için ya kodun en başı olması lazım ya ENDOFLINE'dan sonra başlayan kısım olması lazım ya da '}' yapısından sonra başlyan kısım olmalı bu durumlar haricindeki durumlar hatalıdır.
        if (i == 0 || (i > 0 && (analysisArray[i - 1].itemClass == ENDOFLINE || !strcmp(analysisArray[i - 1].data, "}"))))
        { //Sıradaki yapı special keyword ise bu if bloğu çalışıyor.
            if (analysisArray[i].itemClass == SPECIALKEYWORD)
            {
                int groupID = specialWordGetGroup(analysisArray[i].data); //Special keywordlari benzerlikleri açısından gruplara ayırdık. İlk önce special keywordün hangi gropta olduğunu belirliyoruz.
                if (groupID == 3)                                         // Eğer groupID 3 ise special keyword int,long,record,char,float,enum,const veya static olabilir. Bu special keywordlerin yanına sadece variable ismi gelebilir.
                {
                    if (analysisArray[i + 1].itemClass != VARIABLE) //eğer bu special keywordlerin yanına gelen yapı variable değilse hatalı yazım mevcuttur.Hata mesajı yazıyoruz.
                    {
                        errorMessage = "Error 22: Special data types(long , char ... ) use with a variable name. \n";
                        return 0;
                    }
                    else                                           //eğer yanında variable varsa else bloğu çalışır.
                    {                                              // Variable var long var1; gibi
                        if (!strcmp(analysisArray[i].data, "int")) //Eğer special keyword int ise yanına gelen variable da integer variable ya da classı olmayan bir variable olmalı .Yani öreneğin önceden string olarak tanımlanmış bir variableın başına int yazılamaz.
                        {
                            if (searchVariable(analysisArray[i + 1].data) != INTEGER && searchVariable(analysisArray[i + 1].data) != 0) //eğer variableın classı INTEGER veya classız değilse hatalı bir yazımdır.Hata mesajı veriyoruz.
                            {
                                errorMessage = "Error 13: The code must bu end with an end of line chracter (;). \n";
                                return 0;
                            }
                            else //eğer integer veya classız ise classını INTEGER olarak güncelliyoruz.
                            {
                                struct Object o;
                                strcpy(o.data, analysisArray[i + 1].data);
                                o.itemClass = INTEGER;
                                pushVariable(o);
                            }
                        }
                        else // integer haricindeki tüm variable tipleri için else bloğu çalışıyor.
                        {

                            if (searchVariable(analysisArray[i].data) != OBJECT && searchVariable(analysisArray[i].data) != 0) //Eğer variableın classı OBJECT veya classız değilse hatalıdır.Hata mesajı veriyoruz.
                            {
                                errorMessage = "Error 22: Special data types(long , char ... ) use with a variable name. \n";
                                return 0;
                            }
                            else
                            {
                                if (analysisArray[i + 2].itemClass != ENDOFLINE) // int haricindeki speacial keywordların  yanında yazan variablelara herhangi bir veri ataması yapılamaz. Variabledan sonra ENDOFLİNE gelmez ise hatalı yazımdır.Hata mesajı yazıyoruz.
                                {

                                    errorMessage = "Error 23: Special data types(long , char ... ) must be end with an endofline (;)\n";
                                    return 0;
                                }
                                else // Hatalı bir yazım yoksa variableın classını güncelliyoruz.
                                {
                                    struct Object o;
                                    strcpy(o.data, analysisArray[i + 1].data);
                                    o.itemClass = OBJECT;
                                    pushVariable(o);
                                }
                            }
                        }
                    }
                }

                else if (groupID == 2) /// Eğer groupID 2 ise special keyword  break ,goto,continue olabilir. Bu special keywordlerin yanına sadece ENDOFLINE (';')  gelebilir.
                {
                    if (nextItemClass != ENDOFLINE) //Speacial Keywordün yanındaki yapı ENDOFLINE değilse yatalı yazımdır.Hata mesajı yazıyoruz.
                    {
                        errorMessage = "Error 13: The code must bu end with an end of line chracter (;). \n";
                        return 0;
                    }
                    else //Eğer yazımda hata yoksa indexi ilerletiyoruz.
                    {
                        i = i + 1;
                    }
                }
                else if (groupID == 4) //Eğer groupID 4 ise special keyword return olabilir. Bu special keywordün yanına variable, string veya integer gelebilir.
                {
                    if ((nextItemClass == VARIABLE || nextItemClass == INTEGER || nextItemClass == STRING) && analysisArray[i + 2].itemClass == ENDOFLINE) // returnün yanına variable, string veya integer geldikten sonra ENDOFLİNE geldiyse yazım doğrudur ve indexi 2 ierletiyoruz.
                    {
                        i = i + 2;
                    }
                    else if (analysisArray[i + 2].itemClass != ENDOFLINE) //eğer ENDOFLINE gelmediyse returnden sonra gelen yazımı kontrol etmek için returnStateController true olur.
                    {
                        returnStateController = true;
                    }
                }
                else if (groupID == 1) //Eğer groupID 1 ise special keyword if , for veya while olabilir. Bu special keywordlerden sonra ( gelmelidir.
                {
                    if (!strcmp(analysisArray[i + 1].data, "(")) //Eger if , for veya while sonra '(' yapısı gelmiş ise parantez içerisindeki yapıların kontrolünü yapabilmek için specialWordGroup1Flag i true olarak güncelliyoruz.
                    {
                        specialWordGroup1Flag = true;
                        i = i + 1;
                    }
                    else //Eger if , for veya while sonra '(' yapısı gelmemiş ise hatalı bir yazımdır hata mesajı yazıyoruz.
                    {
                        errorMessage = "Error 11: Brackets are not correctly open or close. \n";
                        return 0;
                    }
                }
                else if (groupID == 5) //Eğer groupID 5 ise special keyword do veya else  olabilir. Bu special keywordlerden sonra '{' gelmelidir.
                {
                    if (strcmp(analysisArray[i + 1].data, "{")) // Eğer do veya elseden sonra  '{' gelmiyorsa hatalı bir yazımdır. Hata mesajı yazıyoruz.
                    {
                        errorMessage = "Error 11: Brackets are not correctly open or close. \n";
                        return 0;
                    }
                }
            }
        }
    }
}
//////////////////////////////     SYNTAX ANALYSES FINISH HERE ///////////////////////////////

void writeTheResult(int t, char *data)
{
    FILE *fptr;
    fptr = fopen("lexical.txt", "a");
    if (t == STRING)
    {
        fprintf(fptr, "STRING(%s)\n", data);
        printf("STRING(%s)\n", data);
    }
    else if (t == INTEGER)
    {
        fprintf(fptr, "INTEGER(%s)\n", data);
        printf("INTEGER(%s)\n", data);
    }
    else if (t == OPERATOR)
    {
        fprintf(fptr, "OPERATOR(%s)\n", data);
        printf("OPERATOR(%s)\n", data);
    }
    /*
         else if (token == COMMENT)
        {
            printf("COMMENT(%s)\n", data);
        }
    */
    else if (t == BRACKET)
    {

        fprintf(fptr, "%s", getBracketNamet(data[0]));
        printf("%s", getBracketNamet(data[0]));
    }
    else if (t == ENDOFLINE)
    {
        fprintf(fptr, "ENDOFLINE(%s)\n", data);
        printf("ENDOFLINE(%s)\n", data);
    }
    else if (t == VARIABLE)
    {
        fprintf(fptr, "VARIABLE(%s)\n", data);
        printf("VARIABLE(%s)\n", data);
    }
    else if (t == SPECIALKEYWORD)
    {
        fprintf(fptr, "SPECIALKEYWORD(%s)\n", data);
        printf("SPECIALKEYWORD(%s)\n", data);
    }
    fclose(fptr);
}

int main()
{
    FILE *fptr;
    fptr = fopen("code.lex", "a");
    read();
    getChar();
    int token;
    while ((token = lexicalAnalyser()) != FINISH)
    {
    }
    struct Object printArr[2048];
    TwoArrayCopy(printArr, analysisArray, 2047);
    if (programFinish)
    {
        checkSyntax();
        for (int i = 0; i < printCounter; i++)
        {

            writeTheResult(printArr[i].itemClass, printArr[i].data);
        }
        if (printCounter == analysisArrayIndex - 1)
        {
            fprintf(fptr, "Program is analyzed -Syntax and Lexically- successfully. \n");
            printf("Program is analyzed -Syntax and Lexically- successfully. \n");
        }
        else
        {
            fprintf(fptr, "%s \n", errorMessage);
            printf("%s \n", errorMessage);
        }
    }
    else
    {
        for (int i = 0; i < analysisArrayIndex; i++)
        {
            writeTheResult(analysisArray[i].itemClass, analysisArray[i].data);
        }
        printf("%s", errorMessage);
        fprintf(fptr, "%s \n", errorMessage);
    }
    fclose(fptr);
}
