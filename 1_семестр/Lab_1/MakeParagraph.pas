{������������ �. �. ��-21. ���-1, �-7}
PROGRAM MakeParagraph(INPUT, OUTPUT);
CONST
  Indent = '     ';      {��������� ��������� �������}
  Space = ' ';
  ExclamationSign = '!';
  QuestionSign = '?';
  Dot = '.';
  PointParagraph = '#';  {���� �� ����������� �� ��������� ����� ��������� �������}
  PointDivide = '$';     {���� �� ����������� �� ��������� ����� �������� ������}
  MaxSentences = 3;      {��������� ������������� ���������� ����������� � ������}
  Sentence = 1;
  
VAR
  Ch: CHAR;
  TemporaryFile: TEXT;          {��������� ����, � ������� ���������� ����������� �����}
  CheckText, CheckEnd: BOOLEAN; {����������� ����������: CheckText - ���� ��� �������� �������, CheckEnd - �������� �������� [., !, ?]}
  Count: INTEGER;               {���������� �������� �����������}

{��������� �������� ������������ ����� 
� ����������� (�������� �� ��� ������ �����������)}  
PROCEDURE CheckCorrectnessDot(VAR CheckEnd: BOOLEAN; VAR Ch: CHAR); 
BEGIN{CheckCorrectnessDot}
  READ(INPUT, Ch);        {���. ���������� ������� ��� ��������}
  IF Ch <> Space          {�������� ���� �� ����� ����� ������, ���� ���� ������ ����� �����������}
  THEN
    CheckEnd := FALSE
  ELSE
    CheckEnd := TRUE;
  WRITE(TemporaryFile, Ch) {����� ������� �� ��������� ����}
END;{CheckCorrectnessDot}

{��������� �������� ������������ ���������������� ����� 
� ����������� (�������� �� �� ������ �����������)}
PROCEDURE CheckCorrectnessExclamationSign(VAR CheckEnd: BOOLEAN; VAR Ch: CHAR);
BEGIN{CheckCorrectnessExclamationSign}
  READ(INPUT, Ch);
  IF Ch <> Space        {�������� ���� �� ����� ����� ������, ���� ���� ������ ����� �����������}
  THEN
    CheckEnd := FALSE
  ELSE
    CheckEnd := TRUE;
  WRITE(TemporaryFile, Ch)
END;{CheckCorrectnessExclamationSign}

{��������� �������� ������������ ��������������� ����� 
� ����������� (�������� �� �� ������ �����������)}
PROCEDURE CheckCorrectnessQuestionSign(VAR CheckEnd: BOOLEAN; VAR Ch: CHAR);
BEGIN{CheckCorrectnessQuestionSign}
  READ(INPUT, Ch);
  IF Ch <> Space         {�������� ���� �� ����� ����� ������, ���� ���� ������ ����� �����������}
  THEN
    CheckEnd := FALSE
  ELSE
    CheckEnd := TRUE;
  WRITE(TemporaryFile, Ch)
END;{CheckCorrectnessQuestionSign}

{��������� ������ �� ���������� ����� � OUTPUT ��������� �������}
PROCEDURE PrintIndent(VAR TemporaryFile: TEXT; VAR Ch: CHAR);
BEGIN{PrintIndent}
  WRITELN(OUTPUT);
  WRITE(OUTPUT, Indent);
  READ(TemporaryFile, Ch);
  WRITE(OUTPUT, Ch)
END;{PrintIndent}

{��������� ������ �� ���������� ����� � OUTPUT �������� ������}
PROCEDURE PrintDivide(VAR TemporaryFile: TEXT; VAR Ch: CHAR);
BEGIN{PrintDivide}
  WRITELN(OUTPUT);
  READ(TemporaryFile, Ch);
  IF Ch = PointParagraph  {��������: ���� �� ������� ����� 3 ����������� � ������}
  THEN
    BEGIN
      WRITE(OUTPUT, Indent);
      READ(TemporaryFile, Ch)
    END;
  WRITE(OUTPUT, Ch)
END;{PrintDivide}

{��������� �������� �� ������� �����}
PROCEDURE CheckEOLN(VAR TemporaryFile: TEXT);
BEGIN{CheckEOLN}
  IF EOLN(INPUT)
  THEN
    BEGIN
      WRITE(TemporaryFile, Ch); {������ �������}
      WRITE(TemporaryFile, PointDivide);
      READLN(INPUT)
    END 
END;{CheckEOLN} 

BEGIN{MakeParagraph}
  REWRITE(TemporaryFile);  {���������� ���������� ����� � ������}
  Count := 0;              {������������� �������� �����������}
  CheckText := TRUE;       {������������� ����� ������ � �����}
  CheckEnd := FALSE;       {������������� ����� �������� �������� (., !, ?)}
  WHILE NOT EOF(INPUT)     {������ ������ �� ����� �����}
  DO
    BEGIN
      WHILE (CheckText) AND (NOT EOF(INPUT)) {���� �������� ���� �� ��������� ���������� ��� ������ � �� ����� �����}
      DO
        BEGIN
          READ(INPUT, Ch);   {���������� �������}
          IF EOLN(INPUT)   {�������� �� ������� ������}
          THEN
            BEGIN
              WRITE(TemporaryFile, Ch); {������ �������}
              WRITE(TemporaryFile, PointDivide); {������ �� ��������� ���� ����� �������� ������}
              READLN(INPUT)
            END
          ELSE
            BEGIN
              WRITE(TemporaryFile, Ch); {������ �������}
              CASE Ch OF     {�������� ���������� ������� �� ������������ (., !, ?) � �������������� � ����� �����������}
                Dot: CheckCorrectnessDot(CheckEnd, Ch); {���� ������ �������� ������ �����������, �� ��������� CheckEnd � ��������� TRUE}
                ExclamationSign: CheckCorrectnessExclamationSign(CheckEnd, Ch);
                QuestionSign: CheckCorrectnessQuestionSign(CheckEnd, Ch);
              ELSE
                CheckEnd := FALSE                       
              END;
              CheckEOLN(TemporaryFile);
              IF CheckEnd           {���� CheckEnd = TRUE, �� ��������� ��������}
              THEN
                Count := Count + Sentence; 
              IF Count = MaxSentences   {���� ��������� 3 �����������, �� ������������� ���������� ������, ���� �� ���������� ���� ��������� �������}
              THEN
                CheckText := FALSE
            END   
        END;  
      IF CheckText = FALSE
      THEN
        BEGIN
          WRITE(TemporaryFile, PointParagraph); {������ �� ��������� ���� ��������� �������}      
          Count := 0;                             {��������� ��������}
          CheckText := TRUE;                      {������������� ���� �� ����������� ���������� ������}
        END
    END; 
  RESET(TemporaryFile);                       {�������������� ��������� ���� � ���������� ��������}
  WRITE(OUTPUT, Indent);                      {������� �������� ������ � ������ 1-�� �����������}
  WHILE NOT EOF(TemporaryFile)                {������ ������ �� ����� �����}
  DO
    BEGIN
      READ(TemporaryFile, Ch);
      CASE Ch OF                              {�������� ���������� ������� �� ����� ��������� ������� � �������� ������: �� - ���������� � �������������� ����������, ��� - ������� ������}
        PointParagraph: PrintIndent(TemporaryFile, Ch);
        PointDivide: PrintDivide(TemporaryFile, Ch)
      ELSE
        WRITE(OUTPUT, Ch)
      END
    END     
END.{MakeParagraph}
