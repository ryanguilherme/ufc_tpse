### Ryan Guilherme Morais Nascimento (512010)

<hr>

# **QUESTÕES**
<hr>


# **Question 10-1:** Example 10 -4 generates the answer 47 instead of the expected answer 144. Why? (See the hint below.)
## **Example 10-4. first/first.c**
<code style='color:pink'>
#include &ltstdio.h&gt
#define FIRST_PART  7<br>
#define LAST_PART 5<br>
#define ALL_PARTS  FIRST_PART + LAST_PART<br><br>
int main() {<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printf("The square of all the parts is %d\n", ALL_PARTS * ALL_PARTS);<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return (0);<br>
}
</code>
<br><br><hr>

### **Reposta:**
### em <code style='color:pink'>define ALL_PARTS FIRST_PART + LAST_PART</code> não há parênteses, logo não foi definida uma ordem de precedência. Nesse sentido, o comando <code style='color:pink'>ALL_PARTS * ALL_PARTS</code> está fazendo <code style='color:pink'>FIRST_PART + LAST_PART * FIRS_PART + LAST_PART</code> ao invés de <code style='color:pink'>(FIRST_PART + LAST_PART) * (FIRST_PART + LAST_PART)</code>
<hr>

# **Question 10-4:** Example 10 -7 is supposed to print the message "Fatal Error: Abort" and exit when it receives bad data. But when it gets good data, it exits. Why?
## **Example 10-7. die/die.c**
<code style='color:pink'>
#include &ltstdio.h&gt<br>
#include &ltstdlib.h&gt<br><br>
#define DIE \<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;fprintf(stderr, "Fatal Error:Abort\n");exit(8);<br><br>
int main() {<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;/* a random value for testing */<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int value;<br><br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;value = 1;<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;if (value < 0)<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;DIE;<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printf("We did not die\n");<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return (0);<br>
}
</code>
<br><br><hr>

### **Resposta:**
### ao deixar o comando <code style='color:pink'>if (value < 0)</code> sem escopo, não há um limite definido, logo o compilador entende que as outras funções chamadas após o DIE fazem parte desse if. Nesse sentido elas não são executadas e o programa acaba.
<hr>

# **Question 10-5:** What does Example 10-8 output? Try running it on your machine. Why did it output what it did? Try checking the output of the preprocessor.
## **Example 10-8. sqr/sqr.c**
<code style='color:pink'>
#include &ltstdio.h&gt<br><br>
#define SQR(x) (x * x)<br><br>
int main(){<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int counter; /* counter for loop */ <br><br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;for (counter = 0; counter < 5; ++counter) {<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printf("x %d, x squared %d\n",counter+1, SQR(counter+1));<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}<br><br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return (0);<br>
}
</code>
<br><br><hr>

### **Resposta:**
### por não ser definida uma prioridade para cada x individualmente, por exemplo: ao invés de <code style='color:pink'>#define SQR(x) (x * x)</code> fosse <code style='color:pink'>#define SQR(x) ((x) * (x))</code>, ao invés do programa fazer o esperado que seria ((x+1)*(x+1)) ele faz (x + 1 * x + 1). Isso acontece porque como não é definida uma prioridade para o x individualmente, que no caso seria (x), o comando não vai reconhecer as somas realizadas ao x na passagem da função como parte do x, e sim como um comando extra na função.
<hr>

# **Question 10-6:** Why will Example 10-9 not produce the expected output? By how much will the counter go up each time?
## **Example 10-9. sqr-i/sqrc-i.c**
<code style='color:pink'>
#include &ltstdio.h&gt<br><br>
#define SQR(x) ((x) * (x))<br><br>
int main(){<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int counter; /* counter for loop */<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Counter = 0;<br><br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;while (counter < 5)<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printf("x %d square %d\n", counter, SQR(++counter));<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return (0);<br>
}
</code>
<br><br><hr>

### **Resposta:**
### o primeiro possível erro (pois pode ter sido um erro de digitação), é a declaração <code style='color:pink'>Counter = 0</code>. Como a linguagem C é case sensitive (letras maísculas diferem de minúsculas, logo counter e Counter são variáveis diferentes), o comando já travaria nessa linha pois tentaria atribuir 0 à uma variável não declarada. Desconsiderando esse erro, se o programa entrasse no while, não iria reproduzir a saída esperada pois <code style='color:pink'>++counter</code> está entrando em <code style='color:pink'>SQR(x) ((x) * (x))</code> e fazendo <code style='color:pink'>((++x) * (++x))</code>, incrementando x duas vezes a cada laço e reproduzindo uma saída indesejada. O correto seria chamar SQR com counter normal e incrementar counter uma vez após o printf, dessa forma, iria imprimir todos os quadrados de 0 até 4 (< 5).
<hr>

# **Question 10-7:** Example 10-10 tells us that we have an undefined variable number, but our only variable name is counter .
## **Example 10-10. rec/rec.c**
<code style='color:pink'>
#include &ltstdio.h&gt<br>
#define RECIPROCAL (number) (1.0 / (number))<br><br>
int main() {<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;float counter; /* Counter for our table */<br><br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;for (counter = 1.0; counter < 10.0;counter += 1.0) {<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printf("1/%f = %f\n", counter, RECIPROCAL(counter));<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return (0);<br>
}
</code>
<br><br><hr>

### **Resposta:**
### O macro RECIPROCAL tenta executar com uma variável "number", porém, como RECIPROCAL não possui parâmetros, para sua execução ser possível seria necessário que number fosse uma variável global declarada, ou que ele possuísse number como parâmetro assim: RECIPROCAL(number).
<hr>
<br>
<hr>

# **EXERCÍCIOS**

# **Exercise 10-1:** Write a macro that returns TRUE if its parameter is divisible by 10 and FALSE otherwise.

### **Resposta:**
<code style='color:pink'>#define divisible(value) (((value % 10) == 0) ? 1 : 0)</code>
<hr>

# **Exercise 10-2:** Write a macro is_digit that returns TRUE if its argument is a decimal digit.

### **Resposta:**
<code style='color:pink'>#define is_digit(value) ((value - (int)value) > 0 ? 1 : 0)</code>
<hr>

# **Exercise 10-3:** Write a second macro is_hex that returns true if its argument is a hex digit (0-9, A-F, a-f). The second macro should reference the first.

### **Resposta:**
<hr>

# **Exercise 10-4:** Write a preprocessor macro that swaps two integers. (For the real hacker, write one that does not use a temporary variable declared outside the macro.)

### **Resposta:**
<code style='color:pink'>#define swap(value, svalue) int hold = svalue; svalue = value; value = hold; </code>