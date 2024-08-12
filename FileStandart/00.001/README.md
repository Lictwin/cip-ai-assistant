# Версія файла / Версия файла / File version 00.001

- [Мова](#бінарны-файл-фармат-dnb)
- [Язык](#бинарный-файл-формат-dnb)
- [Language](#binary-file-format-dnb)

## Бінарны файл фармат .dnb

Файл складаецца з некалькіх частак, што ўмоўна называюцца: 

1. Загаловак (в колькасці 1 штука)
2. Апісанне слаёў (у колькасці слаёў, паказаным у загалоўку)
3. Зарэзерваванае поле (128 байтаў запоўнены нулямі)
4. Апісанне нейронаў (у колькасці, паказаным у пластах; Апісанне нейронаў адбываецца пасля апісання ўсіх слаёў)
5. Метададзеныя (на дадзены момант не падтрымліваецца)Описание слоёв (в количестве слоёв, указанном в заголовке)

### Загаловак файла

|    Апісанне поля     | Колькасць байт     |    Тып дадзенных поля| Тлумачэнне |
|--------------------|----------| ------------- |-----|
| Версія файла | 7 | char |
| Зрух па прагназаванні | 8 | size_t | наколькі адносна апошняга значэння зрушваецца прагназаванне НС
| Зрух па дадзеных | 8 | size_t | наколькі пазіцый адбываецца зрух па дадзеных пасля кожнай ітэрацыі прагназавання
| Агульная памылка прагназавання | 8 | double | Значэнне сярэднеквадратовае памылкі, да якое было атрымана пры апошнім навучанні НС
| Пашпартная памылка | 8 | double | Значэнне сярэднеквадратовае памылкі, да якога імкнуліся пры апошнім навучанні НС
| Максімальная памылка | 8 | double | максімальнае значэнне сярэднеквадратовае памылкі, якое было атрымана пры апошнім навучанні НС
| Мінімальная памылка | 8 | double | мінімальнае значэнне сярэднеквадратовае памылкі, якое было атрымана пры апошнім навучанні НС
| Колькасць параметраў адпраўляюцца на ўваход нейронавай сеткі | 8 | size_t | колькасць лікавых з

### Апісанне слаёў нейронавай сеткі 

Структура паўтараецца столькі разоў, якое Колькасць слаёў у нейронавай сеткі

|    Апісанне поля     | Колькасць байт     |    Тып дадзенных поля| Тлумачэнне |
|--------------------|----------| ------------- |-----|
| Колькасць нейронаў у пласце | 8 | size_t |
| Тып падлучэння да папярэдняга пласту | 1 | bool | дадзенае поле дазваляе вызначыць тып падлучэння true-усё нейроны папярэдняга пласта да ўсіх дадзенага пласта, false-кожны нейрон папярэдняга пласта да вызначанага дадзенага пласта; пры падключэнні першага пласта параўноўваюцца параметры колькасць параметраў адпраўляюцца на ўваход нейронавай сеткі і колькасць нейронаў у першым пласце нейронавай сеткі
| Тып актывацыйны функцыі | 8 | size_t | наколькі пазіцый адбываецца


### Зарэзерваваныя паля

Уяўляе 128 сімвалаў '0' тыпу char

### Апісанне нейронаў нейронавай сеткі

Колькасць структур паўтараецца столькі разоў, колькі находяится ў пластах нейронавай сеткі

|    Апісанне поля     | Колькасць байт     |    Тып дадзенных поля| Тлумачэнне |
|--------------------|----------| ------------- |-----|
| Зрух т | 8 | double | параметр т для нейрона
| Функцыя актывацыі нейрона | 8 | size_t |
| Параметр а для функцыі актывацыі нейрона | 8 | double | пры адсутнасці неабходнасці проста ігнаруецца пры счытванні файла
| Параметр b для функцыі актывацыі нейрона | 8 | double | пры адсутнасці неабходнасці проста ігнаруецца пры счытванні файла
| Колькасць сувязяў у нейроне | 8 | size_t | вызначае памернасць параметру W
| Вагі W | 8 | масіў double | вызначае значэння W ў колькасці які атрымліваецца ад папярэдняга поля (колькасць сувязяў у нейроне)

## Тэкставы файлавы фармат .dnt

Не прадугледжаны, шукай у наступных рэдакцыях фармату.

## Бинарный файл формат .dnb

Файл состоит из нескольких частей, что условно именуются: 

1. Заголовок (в количестве 1 штука)
2. Описание слоёв (в количестве слоёв, указанном в заголовке)
3. Зарезервированное поле (128 байт заполненных нулями)
4. Описание нейронов (в количестве, указанном в слоях; Описание нейронов происходит после описания всех слоёв)
5. Метаданные (на данный момент не поддерживается)

### Заголовок файла

|    Описание поля     | Количество байт     |    Тип данных поля| Пояснение |
|--------------------|----------| ------------- |-----|
| Версия файла               | 7        |   char |
| Сдвиг по прогнозированию               | 8        |  size_t | Насколько относительно последнего значения сдвигается прогнозирование НС
| Сдвиг по данным          | 8        |  size_t | Насколько позиций происходит сдвиг по данным после каждой иттерации прогнозирования
| Общая ошибка прогнозирования | 8        |  double| Значение среднеквадратичной ошибки, к которое было получено при последнем обучении НС
| Пасспортная ошибка                | 8        |  double| Значение среднеквадратичной ошибки, к которому стремились при последнем обучении НС
| Максимальная ошибка   | 8        |  double|  Максимальное значение среднеквадратичной ошибки, которое было получено при последнем обучении НС
| Минимальная ошибка          | 8        |  double| Минимальное значение среднеквадратичной ошибки, которое было получено при последнем обучении НС
| Количество параметров отправляемых на вход нейронной сети  | 8        |  size_t | количество числовых значений отправляемых на вход нейронной сети для прогнозирования
| Количество слоев нейронной сети  | 8        |  size_t |

### Описание слоёв нейронной сети 

Структура повторяется столько раз, каково количество слоёв в нейронной сети

|    Описание поля     | Количество байт     |    Тип данных поля| Пояснение |
|--------------------|----------| ------------- |-----|
| Количество нейронов в слое | 8        |   size_t |
| Тип подключения к предыдущему слою | 1        |  bool | данное поле позволяет определить тип подключения true - все нейроны предыдущего слоя ко всем данного слоя, false  - каждый нейрон предыдущего слоя к определенному данного слоя; при подключении первого слоя сравниваются параметры количество параметров отправляемых на вход нейронной сети и количество нейронов в первом слое нейронной сети
| Тип активационной функции         | 8        |  size_t | Насколько позиций происходит 


### Зарезервированные поля

Представляет 128 символов '0' типа char

### Описание нейронов нейронной сети

количество структур повторяется столько раз, сколько находяится в слоях нейронной сети 

|    Описание поля     | Количество байт     |    Тип данных поля| Пояснение |
|--------------------|----------| ------------- |-----|
| Сдвиг Т | 8        |   double | параметр Т для нейрона
| Функция активации нейрона | 8        |   size_t |
| Параметр а для функции активации нейрона | 8        |  double | При отсутствии необходимости просто игнорируется при считывании файла
| Параметр b для функции активации нейрона | 8        |  double | При отсутствии необходимости просто игнорируется при считывании файла
| Количество связей в нейроне   | 8        |  size_t | определяет размерность параметра W
| Веса W  | 8        |  массив double | определяет значения W в количестве получаемом от предыдущего поля (Количество связей в нейроне)

## Текстовый файловый формат .dnt

Не предусмотрен, ищи в следующих редакциях формата.

## Binary file format .dnb

The file consists of several parts, which are conventionally called: 

1. Header (in the amount of 1 piece)
2. Description of the layers (in the number of layers specified in the header)
3. Reserved field (128 bytes filled with zeros)
4. Description of neurons (in the number indicated in the layers; The description of neurons occurs after the description of all layers)
5. Metadata (currently not supported)

### File header

| Field description | Number of bytes | Field data type| Explanation |
|--------------------|----------| ------------- |-----|
| File version | 7 | char |
| Prediction shift | 8 | size_t | How much does the prediction shift relative to the last value?
| Data shift | 8 | size_t | How many positions does the data shift after each iteration of forecasting
| Total prediction error | 8 | double| The value of the root-mean-square error, which was obtained during the last training of the NS
| Passport error | 8 | double| The value of the root-mean-square error, which was sought during the last training of the NS
| Maximum error | 8 | double| The maximum value of the root-mean-square error that was obtained during the last NS training
| Minimum error | 8 | double| The minimum value of the root-mean-square error that was obtained during the last NS training
| Number of parameters sent to the input of the neural network | 8 | size_t | number of numeric values sent to the input of the neural network for prediction
| Number of neural network layers | 8 | size_t |

### Description of neural network layers 

The structure is repeated as many times as the number of layers in the neural network

| Field description | Number of bytes | Field data type| Explanation |
|--------------------|----------| ------------- |-----|
| Number of neurons in the layer | 8 | size_t |
| Connection type to the previous layer | 1 | bool | this field allows you to determine the type of connection true - all neurons of the previous layer to all of this layer, false - each neuron of the previous layer to a specific one of this layer; when connecting the first layer, the parameters are compared the number of parameters sent to the input of the neural network and the number of neurons in the first layer of the neural network
| Type of activation function | 8 | size_t | How many positions are there 


### Reserved fields

Represents 128 '0' characters of the char type

### Description of neurons in a neural network

the number of structures is repeated as many times as it is in the layers of the neural network 

| Field description | Number of bytes | Field data type| Explanation |
|--------------------|----------| ------------- |-----|
| Shift T | 8 | double | parameter T for neuron
| Neuron activation function | 8 | size_t |
| Parameter a for the neuron activation function | 8 | double | If not necessary, it is simply ignored when reading the file.
| Parameter b for the neuron activation function | 8 | double | If not necessary, it is simply ignored when reading the file.
| The number of connections in a neuron | 8 | size_t | determines the dimension of the parameter W
| Weights W | 8 | array double | defines the values of W in the amount received from the previous field (The number of connections in the neuron)

## Text file format .dnt

It is not provided, look in the following editions of the format.