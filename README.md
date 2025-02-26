## Projeto-U7

**Objetivo do Projeto:**

O objetivo deste projeto é criar um simulador de estoque utilizando uma matriz 5x5 de LEDs (WS2812) do BitDogLab, simulando o estoque de diferentes produtos de um hortifrúti. A matriz de LEDs será usada para representar a quantidade de cada tipo de produto disponível, sendo que cada cor de LED corresponderá a um tipo de fruta. O sistema de controle do estoque será feito por meio de um joystick e botões, permitindo selecionar e modificar a quantidade de produtos disponíveis nas colunas da matriz de LEDs. Além disso, LEDs indicadores serão usados para fornecer feedback visual sobre o status do estoque, como a falta de produto, estoque cheio ou produtos quase acabando.

**Descrição do Funcionamento:**

1. **Estrutura da Matriz de LEDs:** 🚦

   A matriz de LEDs WS2812 tem dimensões de 5x5, ou seja, é composta por 25 LEDs ao todo. Cada LED será responsável por representar a quantidade de um tipo de produto, sendo que os LEDs terão cores específicas para cada tipo de fruta:
   
   - 🔴 LED **vermelho**: Representa **maçãs** 🍎.
   - 🟡 LED **amarelo**: Representa **bananas** 🍌.
   - 🟢 LED **verde**: Representa **abacates** 🥑.
   - 🟣 LED **roxo**: Representa **uvas** 🍇.
   
   As cores dos LEDs serão manipuladas conforme a quantidade de estoque disponível para cada produto.

2. **Controle do Estoque:** 🎛️
   
   A interação com o sistema de estoque será feita por meio de um joystick e dois botões:
   
   - **Joystick**: O joystick permite selecionar uma das colunas da matriz de LEDs, onde cada coluna representa um produto específico (maçã, banana, abacate ou uva).
   
   - **Botão A (GPIO5)**: Este botão é utilizado para incrementar (adicionar) a quantidade do produto selecionado na coluna ativa. Ao pressioná-lo, a quantidade de LEDs acesos na coluna aumentará.
   
   - **Botão B (GPIO6)**: Este botão é utilizado para decrementar (remover) a quantidade do produto selecionado na coluna ativa. Ao pressioná-lo, a quantidade de LEDs acesos na coluna diminuirá.
   
3. **Indicadores de Status do Estoque:** 🗽

   O sistema inclui três LEDs adicionais conectados a pinos específicos da GPIO para fornecer informações sobre o estado do estoque. Esses LEDs são usados para indicar diferentes condições do estoque, conforme detalhado abaixo:

   - **LED no GPIO13**: Este LED será aceso para indicar que **não há produto** na coluna selecionada. Ou seja, se todos os LEDs da coluna estiverem apagados, o LED de GPIO13 será ativado para sinalizar a ausência do produto.

   - **LED no GPIO11**: Este LED será aceso quando o **estoque estiver cheio**. Caso todos os LEDs da coluna estejam acesos, o LED de GPIO11 será ativado para indicar que a quantidade máxima de produtos foi atingida.

   - **LED no GPIO12**: Este LED será aceso quando a quantidade de um produto na coluna estiver prestes a acabar. Se restar apenas um único LED aceso na coluna, o LED de GPIO12 será ativado para informar que o estoque está quase no fim.

4. **Fluxo do Sistema:** 💾

   - O usuário começa a interação com o sistema usando o joystick para selecionar uma das colunas da matriz de LEDs.
   - O botão A (GPIO5) é pressionado para aumentar a quantidade do produto correspondente à coluna selecionada.
   - O botão B (GPIO6) é pressionado para diminuir a quantidade do produto correspondente à coluna selecionada.
   - O sistema verifica a quantidade de LEDs acesos na coluna selecionada e aciona os LEDs indicadores conforme o estado do estoque, ou seja, se o estoque estiver vazio, cheio ou quase acabando.

5. **Considerações Técnicas:** 👨‍💻

   - A matriz de LEDs WS2812 será controlada por meio de um microcontrolador, que também gerenciará os botões e os LEDs indicadores.
   - O uso do joystick e dos botões permite uma interface simples e intuitiva para o usuário interagir com o sistema de estoque.
   - O projeto foi desenvolvido de maneira a oferecer feedback visual claro e imediato sobre o estado do estoque, facilitando a gestão dos produtos.

**Conclusão:** ✔️

O simulador de estoque criado com a matriz de LEDs WS2812 oferece uma maneira visual e interativa de gerenciar o estoque de produtos de um hortifrúti. O uso de LEDs coloridos para representar diferentes tipos de frutas, combinado com o controle simples por joystick e botões, proporciona uma experiência fácil de usar e eficiente para simular a gestão de estoque. Além disso, os LEDs indicadores de estado do estoque oferecem informações claras sobre a quantidade de produtos disponíveis, ajudando a evitar a falta de estoque ou o excesso de produtos.

Este projeto pode ser expandido e adaptado para simulações mais complexas ou para aplicações em contextos reais de gerenciamento de estoque, caso necessário.
