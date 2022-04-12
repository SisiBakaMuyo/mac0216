# TECPROG-2019
O objetivo deste projeto é o desenvolvimento de um programa composto de várias partes (módulos) ao longo do semestre.

Os módulos serão construídos ao longo de algumas fases (4) sendo uma das fases a  "amarração" e construção do programa final.

Serão consideradas a documentação e a organização do código, além do seu funcionamento. Os módulos devem ser tão independentes quanto possível e a comunicação entre dois módulos só deverá ser feita através de uma interface bem definida.

Padrão no arquivo de entrada.
2.1 Arquivo de entrada
A entrada será fornecida em um arquivo com o seguinte formato:

    A primeira linha tem os parâmetros globais, separados por espaço:
        Tamanho do planeta (raio). Em Raios terrestres (RT)
        Massa do planeta.	Em massa terrestres (M_T)
        Tempo total de simulação. Em segundos
    A segunda linha contém a descrição da primeira nave, com os seguintes campos separados por espaço:
        nome — nome da nave, para referência posterior.
        massa — massa da nave. Em quilograms (kg)
        pos_x — coordenada x da posição da nave. Em metros (m)
        pos_y — coordenada y da posição da nave. Em metros (m)
        vel_x — componente x da velocidade da nave. Em metros por segundo (m/s)
        vel_y — componente y da velocidade da nave. Em metros por segundo (m/s)
    A terceira linha descreve a segunda nave, da mesma forma.
    A quarta linha indicará o número de projéteis e a duração (tempo de vida) deles.
    As linhas seguintes conterão a descrição de cada projétil, da mesma forma que nas naves, mas sem o campo nome.
