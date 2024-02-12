{Габдрахманов Е. Н. ПС-21. Лаб-1, В-7}
PROGRAM MakeParagraph(INPUT, OUTPUT);
CONST
  Indent = '     ';      {Константа абзацного отступа}
  Space = ' ';
  ExclamationSign = '!';
  QuestionSign = '?';
  Dot = '.';
  PointParagraph = '#';  {Флаг на обозначение во временном файле абзацного отступа}
  PointDivide = '$';     {Флаг на обозначение во временном файле переноса строки}
  MaxSentences = 3;      {Константа максимального количества предложений в абзаце}
  Sentence = 1;
  
VAR
  Ch: CHAR;
  TemporaryFile: TEXT;          {Временный файл, в который записываем прочитанный текст}
  CheckText, CheckEnd: BOOLEAN; {Проверочные переменные: CheckText - флаг для счетчика абзацов, CheckEnd - проверка символов [., !, ?]}
  Count: INTEGER;               {Переменная счетчика предложений}

{Процедура проверки корректности точки 
в предложении (является ли она концом предложения)}  
PROCEDURE CheckCorrectnessDot(VAR CheckEnd: BOOLEAN; VAR Ch: CHAR); 
BEGIN{CheckCorrectnessDot}
  READ(INPUT, Ch);        {Доп. считывание символа для проверки}
  IF Ch <> Space          {Проверка есть ли после знака пробел, если есть значит конец предложения}
  THEN
    CheckEnd := FALSE
  ELSE
    CheckEnd := TRUE;
  WRITE(TemporaryFile, Ch) {Вывод символа во временный файл}
END;{CheckCorrectnessDot}

{Процедура проверки корректности восклицательного знака 
в предложении (является ли он концом предложения)}
PROCEDURE CheckCorrectnessExclamationSign(VAR CheckEnd: BOOLEAN; VAR Ch: CHAR);
BEGIN{CheckCorrectnessExclamationSign}
  READ(INPUT, Ch);
  IF Ch <> Space        {Проверка есть ли после знака пробел, если есть значит конец предложения}
  THEN
    CheckEnd := FALSE
  ELSE
    CheckEnd := TRUE;
  WRITE(TemporaryFile, Ch)
END;{CheckCorrectnessExclamationSign}

{Процедура проверки корректности вопросительного знака 
в предложении (является ли он концом предложения)}
PROCEDURE CheckCorrectnessQuestionSign(VAR CheckEnd: BOOLEAN; VAR Ch: CHAR);
BEGIN{CheckCorrectnessQuestionSign}
  READ(INPUT, Ch);
  IF Ch <> Space         {Проверка есть ли после знака пробел, если есть значит конец предложения}
  THEN
    CheckEnd := FALSE
  ELSE
    CheckEnd := TRUE;
  WRITE(TemporaryFile, Ch)
END;{CheckCorrectnessQuestionSign}

{Процедура вывода из временного файла в OUTPUT абзацного отступа}
PROCEDURE PrintIndent(VAR TemporaryFile: TEXT; VAR Ch: CHAR);
BEGIN{PrintIndent}
  WRITELN(OUTPUT);
  WRITE(OUTPUT, Indent);
  READ(TemporaryFile, Ch);
  WRITE(OUTPUT, Ch)
END;{PrintIndent}

{Процедура вывода из временного файла в OUTPUT переноса строки}
PROCEDURE PrintDivide(VAR TemporaryFile: TEXT; VAR Ch: CHAR);
BEGIN{PrintDivide}
  WRITELN(OUTPUT);
  READ(TemporaryFile, Ch);
  IF Ch = PointParagraph  {Проверка: идет ли перенос после 3 предложения в абзаце}
  THEN
    BEGIN
      WRITE(OUTPUT, Indent);
      READ(TemporaryFile, Ch)
    END;
  WRITE(OUTPUT, Ch)
END;{PrintDivide}

{Процедура проверки на перенос строк}
PROCEDURE CheckEOLN(VAR TemporaryFile: TEXT);
BEGIN{CheckEOLN}
  IF EOLN(INPUT)
  THEN
    BEGIN
      WRITE(TemporaryFile, Ch); {Запись символа}
      WRITE(TemporaryFile, PointDivide);
      READLN(INPUT)
    END 
END;{CheckEOLN} 

BEGIN{MakeParagraph}
  REWRITE(TemporaryFile);  {Подготовка временного файла к записи}
  Count := 0;              {Инициализация счетчика предложений}
  CheckText := TRUE;       {Инициализация флага текста в файле}
  CheckEnd := FALSE;       {Инициализация флага проверки символов (., !, ?)}
  WHILE NOT EOF(INPUT)     {Защита чтения на конец файла}
  DO
    BEGIN
      WHILE (CheckText) AND (NOT EOF(INPUT)) {Цикл работает пока не набралось преложений для абзаца и не конец файла}
      DO
        BEGIN
          READ(INPUT, Ch);   {Считывание символа}
          IF EOLN(INPUT)   {Проверка на перенос строки}
          THEN
            BEGIN
              WRITE(TemporaryFile, Ch); {Запись символа}
              WRITE(TemporaryFile, PointDivide); {Запись во временный файл флага переноса строки}
              READLN(INPUT)
            END
          ELSE
            BEGIN
              WRITE(TemporaryFile, Ch); {Запись символа}
              CASE Ch OF     {Проверка считанного символа на корректность (., !, ?) и принадлежность к концу предложения}
                Dot: CheckCorrectnessDot(CheckEnd, Ch); {Если символ является концом предложения, то переводим CheckEnd в состояние TRUE}
                ExclamationSign: CheckCorrectnessExclamationSign(CheckEnd, Ch);
                QuestionSign: CheckCorrectnessQuestionSign(CheckEnd, Ch);
              ELSE
                CheckEnd := FALSE                       
              END;
              CheckEOLN(TemporaryFile);
              IF CheckEnd           {Если CheckEnd = TRUE, то инкримент счетчика}
              THEN
                Count := Count + Sentence; 
              IF Count = MaxSentences   {Если набралось 3 предложения, то останавливаем считывание текста, пока не уставновим флаг абзацного отступа}
              THEN
                CheckText := FALSE
            END   
        END;  
      IF CheckText = FALSE
      THEN
        BEGIN
          WRITE(TemporaryFile, PointParagraph); {Запись во временный файл абзацного отступа}      
          Count := 0;                             {Обнуление счетчика}
          CheckText := TRUE;                      {Устанавливаем флаг на продолжение считывание текста}
        END
    END; 
  RESET(TemporaryFile);                       {Подготавливаем временный файл к считыванию символов}
  WRITE(OUTPUT, Indent);                      {Выводим абзацный отступ в начале 1-го предложения}
  WHILE NOT EOF(TemporaryFile)                {Защита чтения на конец файла}
  DO
    BEGIN
      READ(TemporaryFile, Ch);
      CASE Ch OF                              {Проверка считанного символа на флаги абзацного отступа и переноса строки: да - обращаемся к соответсвенным процедурам, нет - выводим символ}
        PointParagraph: PrintIndent(TemporaryFile, Ch);
        PointDivide: PrintDivide(TemporaryFile, Ch)
      ELSE
        WRITE(OUTPUT, Ch)
      END
    END     
END.{MakeParagraph}
