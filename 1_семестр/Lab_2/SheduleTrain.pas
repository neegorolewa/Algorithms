{Габдрахманов Е.Н. ПС-21}
{PascalABC.NET 3.8.3}
{18. На   узловой   станции  необходимо  менять  направления
движения всех  поездов.  Для  этого  предназначен  специальный
тупик.  Зашедший  в  тупик  последний  поезд  выходит  из него
первым.  Известны  моменты  прихода   поездов   и   минимально
необходимое   время   стоянки (одинаковое  для всех  поездов).
Требуется:
   1) составить расписание стоянки поездов на станции с учетом
смены направления движения;
   2) поменять   между   собой   моменты   прихода   скорых  и
пассажирских  поездов   так,   чтобы   скорые   поезда   имели
минимальное суммарное время простоя в тупике (9)}
PROGRAM SheduleTrain;
USES
  CRT;
TYPE
  Time = RECORD
           Hour: INTEGER;
           Minute: INTEGER; 
         END;
         
  UkazTupik = ^Tupik; //Основной стек
  Tupik = RECORD
            NumberTrain: INTEGER;
            TypeTrain: CHAR;
            TimeTrain: Time;
            ExitTime: Time;
            ParkingTime: Time;
            DownTime: INTEGER;
            Next: UkazTupik; 
          END;
  UkazTemp = ^Temp; //Временный стек       
  Temp = RECORD
            TempNumberTrain: INTEGER;
            TempTypeTrain: CHAR;
            TempTimeTrain: Time;
            TempExitTime: Time;
            TempParkingTime: Time;
            TempDownTime: INTEGER;
            Next: UkazTemp; 
         END;        
          
CONST
  Fast = 'S';
  Passenger = 'P';
  Empty = '';
  Dot = '.';
  Space = ' ';
  FirBracket = '(';
  SecBracket = ')';
  Nomer = '№';
  
VAR
  ValueDownTime: ARRAY OF INTEGER;
  Ch, TrType: CHAR;
  FileName: STRING;
  H, Min, CountTrain, CountS, Number: INTEGER;
  StopTime: Time;
  TempTrain: UkazTemp;
  NowTrain: UkazTupik;
  InFile: TEXT;
  
PROCEDURE PushTrain(VAR Top: UkazTupik; TrType: CHAR; H, Min, Number: INTEGER);//Добавление поезда в тупик
VAR
  Kon: UkazTupik;
BEGIN{PushTrain}
  NEW(Kon);
  Kon^.Next := Top;
  Kon^.TypeTrain := TrType;
  Kon^.TimeTrain.Hour := H;
  Kon^.TimeTrain.Minute := Min;
  Kon^.NumberTrain := Number;
  Top := Kon
END;{PushTrain} 

PROCEDURE PopCycle(VAR TopTemp: UkazTemp); //Удаление поездов из временного стека
VAR
  KonTemp: UkazTemp;
BEGIN{PopCycle}
  WHILE TopTemp <> NIL
  DO
    BEGIN
      KonTemp := TopTemp;
      TopTemp := TopTemp^.Next;
      DISPOSE(KonTemp)
    END;
END;{PopCycle}

PROCEDURE CleanTupik(VAR Top: UkazTupik; VAR CountS, CountTrain: INTEGER); //Очистка основного тупика
VAR
  Kon: UkazTupik;
BEGIN{CleanTupik}
  WHILE Top <> NIL
  DO
    BEGIN
      Kon := Top;
      Top := Top^.Next;
      DISPOSE(Kon)
    END;
  CountS := 0;
  CountTrain := 0
END;{CleanTupik}

PROCEDURE ReadFile(VAR F: TEXT; VAR CountTrain, CountS: INTEGER);//Чтение файла и запись поездов в основной стек
BEGIN{ReadFile}
  CountS := 0;
  CountTrain := 0;
  READ(F, StopTime.Hour);
  READ(F, StopTime.Minute);
  READLN(F);
  WHILE NOT EOF(F)
  DO
    BEGIN
      READ(F, Number);
      READ(F, Ch);
      READ(F, TrType);
      IF TrType = Fast
      THEN
        CountS += 1;
      READ(F, H);
      READ(F, Min);
      PushTrain(NowTrain, TrType, H, Min, Number);
      CountTrain += 1;
      READLN(F)
    END;
  CLOSE(F)  
END;{ReadFile}

PROCEDURE PushCopyTupik(Top: UkazTupik; VAR TopTemp: UkazTemp); //Перенос элементов из основного стека во временный
VAR
  KonTemp: UkazTemp;
BEGIN{CopyTupik}
  WHILE Top <> NIL
  DO
    BEGIN
      NEW(KonTemp);
      KonTemp^.Next := TopTemp;
      KonTemp^.TempNumberTrain := Top^.NumberTrain;
      KonTemp^.TempTypeTrain := Top^.TypeTrain;
      KonTemp^.TempTimeTrain := Top^.TimeTrain;
      KonTemp^.TempExitTime := Top^.ExitTime;
      KonTemp^.TempParkingTime := Top^.ParkingTime;
      TopTemp := KonTemp;
      Top := Top^.Next
    END
END;

PROCEDURE PrintTupik(TopTemp: UkazTemp); //Вывод тупика(*работа со временным стеком*)
VAR
  Count: INTEGER;
  MinStr: STRING;
PROCEDURE IntToStrMinute(Min: INTEGER; VAR MinStr: STRING);
BEGIN{IntToStr}
  CASE Min OF
    0: MinStr := '00';
    1: MinStr := '01';
    2: MinStr := '02';
    3: MinStr := '03';
    4: MinStr := '04';
    5: MinStr := '05';
    6: MinStr := '06';
    7: MinStr := '07';
    8: MinStr := '08';
    9: MinStr := '09';
  END;
END;{IntToStr}  
BEGIN{OutputTupik}
  ClrScr;
  Count := 1;
  IF TopTemp = NIL
  THEN
    WRITELN('Тупик пуст')
  ELSE
    BEGIN
      WHILE TopTemp <> NIL
      DO
        BEGIN
          IF TopTemp^.TempTimeTrain.Minute > 9
          THEN
            WRITE(Count, SecBracket, Space, Nomer, TopTemp^.TempNumberTrain, Space, TopTemp^.TempTypeTrain, Space, TopTemp^.TempTimeTrain.Hour, Dot, TopTemp^.TempTimeTrain.Minute)
          ELSE
            BEGIN
              IntToStrMinute(TopTemp^.TempTimeTrain.Minute, MinStr);
              WRITE(Count, SecBracket, Space, Nomer, TopTemp^.TempNumberTrain, Space, TopTemp^.TempTypeTrain, Space, TopTemp^.TempTimeTrain.Hour, Dot, MinStr)
            END;
          TopTemp := TopTemp^.Next;
          WRITELN;
          Count += 1
        END;
    END;
  WRITELN('Нажмите любую клавишу, чтобы продолжить...');  
  READKEY  
END;{OutputTupik}

PROCEDURE AddTrain(VAR Top: UkazTupik; VAR CountS, CountTrain: INTEGER); // Добавление одного поезда в тупик
BEGIN{AddTrain}
  WRITE('Введите номер поезда: ');
  READLN(Number);
  WRITE('Введите тип поезда(P-пассажирский/S-скоростной): ');
  READLN(TrType);
  IF TrType = Fast
  THEN
    CountS += 1;
  WRITE('Введите время прибытия(чч<пробел>мм): ');
  READ(H);
  READLN(Min);
  PushTrain(NowTrain, TrType, H, Min, Number);
  CountTrain += 1;
  WRITELN('Нажмите любую клавишу, чтобы продолжить...');  
  READKEY
END;{AddTrain}

PROCEDURE ChangeStopTime(VAR StopTime: Time); //Изменение времени стоянки
VAR
  HourNew, MinNew: INTEGER;
BEGIN{ChangeStopTime}
  WRITE('Введите новое время стоянки(чч<пробел>мм): ');
  READ(HourNew);
  READLN(MinNew);
  StopTime.Hour := HourNew;
  StopTime.Minute := MinNeW;
  WRITELN('Время стоянки изменено на ', StopTime.Hour, Dot, StopTime.Minute);
  WRITELN('Нажмите любую клавишу, чтобы продолжить...');
  READKEY
END;{ChangeStopTime}

PROCEDURE PrintStopTime(StopTime: Time); //Вывод на экран времени стоянки
BEGIN{PrintStopTime}
  WRITELN('Действующее время стоянки: ', StopTime.Hour, Dot, StopTime.Minute);
  WRITELN('Нажмите любую клавишу, чтобы продолжить...');
  READKEY
END;{PrintStopTime}

PROCEDURE CalculationExitTime(StopTime: Time; Top: UkazTupik); //Подсчет времени выхода поезда из тупика
VAR
  PrevTrainTime: INTEGER;
  PrevExitTime: INTEGER;
  FlagFirst: BOOLEAN;
BEGIN{CalculationExitTime}
  PrevTrainTime := 0;
  PrevExitTime := 0;
  FlagFirst := TRUE;
  IF Top = NIL
  THEN
    WRITELN('Действие невозможно. Причина: пустой стек');
  WHILE Top <> NIL
  DO
    BEGIN
      IF FlagFirst
      THEN
        BEGIN
          H := Top^.TimeTrain.Hour;
          Min := Top^.TimeTrain.Minute;
          PrevTrainTime := (H*60) + Min;
          Top^.ExitTime.Hour := (((H*60) + Min) + ((StopTime.Hour * 60) + StopTime.Minute)) DIV 60;
          Top^.ExitTime.Minute := (((H*60) + Min) + ((StopTime.Hour * 60) + StopTime.Minute)) - (Top^.ExitTime.Hour * 60);
          PrevExitTime := Top^.ExitTime.Hour * 60 + Top^.ExitTime.Minute;
          FlagFirst := FALSE; 
          Top := Top^.Next;
        END
      ELSE
        BEGIN
          H := Top^.TimeTrain.Hour;
          Min := Top^.TimeTrain.Minute;
          Top^.ExitTime.Hour := (((H*60) + Min) + ((StopTime.Hour * 60) + StopTime.Minute)) DIV 60;
          Top^.ExitTime.Minute := (((H*60) + Min) + ((StopTime.Hour * 60) + StopTime.Minute)) - (Top^.ExitTime.Hour * 60);
          IF (Top^.ExitTime.Hour*60 + Top^.ExitTime.Minute) > PrevTrainTime
          THEN
            BEGIN
              Top^.ExitTime.Hour := PrevExitTime DIV 60;
              Top^.ExitTime.Minute := PrevExitTime - (Top^.ExitTime.Hour*60)
            END;
          PrevTrainTime := H*60 + Min;
          PrevExitTime := Top^.ExitTime.Hour * 60 + Top^.ExitTime.Minute;  
          Top := Top^.Next
        END;
    END  
END;{CalculationExitTime}


PROCEDURE CalculateParkingTime(Top: UkazTupik); //Подсчет времени стоянки отдельного поезда с учетом простоя
BEGIN{CalculateParkingTime}
  WHILE Top <> NIL
  DO
    BEGIN
      Top^.ParkingTime.Hour := ((Top^.ExitTime.Hour*60 + Top^.ExitTime.Minute) - (Top^.TimeTrain.Hour*60 + Top^.TimeTrain.Minute)) DIV 60;
      Top^.ParkingTime.Minute := ((Top^.ExitTime.Hour*60 + Top^.ExitTime.Minute) - (Top^.TimeTrain.Hour*60 + Top^.TimeTrain.Minute)) - (Top^.ParkingTime.Hour * 60);
      Top := Top^.Next
    END;
END;{CalculateParkingTime}

PROCEDURE PrintShedule(TopTemp: UkazTemp); //Вывод расписания со временем выезда и временем стоянки
VAR
  Count: INTEGER;
  MinStr: STRING;
PROCEDURE IntToStrMinute(Min: INTEGER; VAR MinStr: STRING);
BEGIN{IntToStr}
  CASE Min OF
    0: MinStr := '00';
    1: MinStr := '01';
    2: MinStr := '02';
    3: MinStr := '03';
    4: MinStr := '04';
    5: MinStr := '05';
    6: MinStr := '06';
    7: MinStr := '07';
    8: MinStr := '08';
    9: MinStr := '09';
  END;
END;{IntToStr}
BEGIN{PrintShedule}
  ClrScr;
  Count := 1;
  IF TopTemp = NIL
  THEN
    WRITELN('Тупик пуст');
  WHILE TopTemp <> NIL
  DO
    BEGIN
      IF TopTemp^.TempTimeTrain.Minute > 9
      THEN
          WRITE(Count, SecBracket, Space, Nomer, TopTemp^.TempNumberTrain, Space, TopTemp^.TempTypeTrain, Space, TopTemp^.TempTimeTrain.Hour, Dot, TopTemp^.TempTimeTrain.Minute)
      ELSE
        BEGIN
          IntToStrMinute(TopTemp^.TempTimeTrain.Minute, MinStr);
          WRITE(Count, SecBracket, Space, Nomer, TopTemp^.TempNumberTrain, Space, TopTemp^.TempTypeTrain, Space, TopTemp^.TempTimeTrain.Hour, Dot, MinStr)
        END;
      IF TopTemp^.TempExitTime.Minute > 9
      THEN
        WRITE(' Время выезда: ', TopTemp^.TempExitTime.Hour, Dot, TopTemp^.TempExitTime.Minute)
      ELSE
        BEGIN
          IntToStrMinute(TopTemp^.TempExitTime.Minute, MinStr);
          WRITE(' Время выезда: ', TopTemp^.TempExitTime.Hour, Dot, MinStr)
        END;
      IF TopTemp^.TempParkingTime.Minute > 9
      THEN
        WRITE(' Время стоянки: ', TopTemp^.TempParkingTime.Hour, Dot, TopTemp^.TempParkingTime.Minute)
      ELSE
        BEGIN
          IntToStrMinute(TopTemp^.TempParkingTime.Minute, MinStr);
          WRITE(' Время стоянки: ', TopTemp^.TempParkingTime.Hour, Dot, MinStr)
        END;
      TopTemp := TopTemp^.Next;
      WRITELN;
      Count += 1
    END;
  WRITELN('Нажмите любую клавишу, чтобы продолжить...');  
  READKEY
END;{PrintShedule}

PROCEDURE CalculateDownTime(StopTime: Time; Top: UkazTupik); //Подсчет времени простоя
BEGIN{CalculateDowntime}
  WHILE Top <> NIL
  DO
    BEGIN
      Top^.DownTime := ((Top^.ParkingTime.Hour*60 + Top^.ParkingTime.Minute) - (StopTime.Hour*60 + StopTime.Minute));
      Top := Top^.Next
    END;
END;{CalculateDowntime}
 
PROCEDURE WriteValue(VAR Massiv: ARRAY OF INTEGER; Top: UkazTupik); //Запись в массив время простоя каждого поезда
VAR
  i: INTEGER;
BEGIN{WriteValue}
  IF Top = NIL
  THEN
    WRITELN('Тупик пуст')
  ELSE
    BEGIN
      FOR i := 0 TO (Length(Massiv)-1)
      DO
        BEGIN
          Massiv[i] := Top^.DownTime;
          Top := Top^.Next;
          IF Top = NIL
          THEN
            Break
        END
    END    
END;{WriteValue}

PROCEDURE SortValue(VAR Massiv: ARRAY OF INTEGER); //Сортировка массива со временем простоя(от меньшего к большему)
VAR
  i, j, k: INTEGER;
BEGIN{SortValue}
  FOR i := 1 TO Length(Massiv) - 1 DO
    FOR j := 1 TO (Length(Massiv) - i - 1) DO
      IF Massiv[j] > Massiv[j + 1]
      THEN
        BEGIN
          k := Massiv[j];
          Massiv[j] := Massiv[j + 1];
          Massiv[j + 1] := k
        END;
END;{SortValue}

PROCEDURE MakeArrayOfMinValue(VAR Massiv: ARRAY OF INTEGER; CountS: INTEGER); //Удаление элементов из массива по количеству скорых поездов
VAR
  i: INTEGER;
BEGIN{MakeArrayOfMinValue}
  FOR i := CountS TO Length(Massiv)-1
  DO
    Massiv[i] := -1
END;{MakeArrayOfMinValue}
 
PROCEDURE ChangeTypeTrain(Top: UkazTupik; Massiv: ARRAY OF INTEGER; CountS: INTEGER); //Изменение типа поезда по времени простоя
VAR
  i: INTEGER;
  FlagChange, FlagFind: BOOLEAN;
BEGIN{ChangeTypeTrain}
  FlagChange := FALSE;
  FlagFind := FALSE;
  WHILE Top <> NIL
  DO
    BEGIN
      FOR i := 0 TO Length(Massiv)-1
      DO
        BEGIN
          IF Top^.DownTime = Massiv[i]
          THEN
            BEGIN
              FlagFind := TRUE;
              IF Top^.TypeTrain <> Fast
              THEN
                BEGIN
                  Top^.TypeTrain := Fast;
                  FlagChange := TRUE; 
                END;
              Massiv[i] := -1;
              BREAK
            END 
        END;
      IF (FlagFind = FALSE) AND (FlagChange = FALSE) AND (Top^.TypeTrain = Fast)
      THEN
        Top^.TypeTrain := Passenger;
      Top := Top^.Next;
      FlagChange := FALSE;
      FlagFind := FALSE
    END
END;{ChangeTypeTrain}
 
BEGIN{SheduleTrain}

  FileName := Empty;  
  WRITE('Введите имя файла, с которым желаете начать работу: ');
  IF NOT EOLN  
  THEN
    BEGIN
      READLN(FileName);  
      IF FileExists(FileName)
      THEN    
        BEGIN
          ASSIGN(InFile, FileName);      
          RESET(InFile);
        END  
      ELSE
        BEGIN      
          WRITELN('Произошла ошибка при открытии файла');
          READKEY;
          EXIT
        END
    END;
    
  NowTrain := NIL;
  ReadFile(InFile, CountTrain, CountS);
  SetLength(ValueDownTime, CountTrain); //Определение размера массива по количеству поездов
  PushCopyTupik(NowTrain, TempTrain);
  WHILE TRUE
  DO
    BEGIN
      ClrScr;
      WRITELN('(1) Вывести поезда в тупике;');
      WRITELN('(2) Загнать поезд в тупик;');
      WRITELN('(3) Изменить время стоянки;');
      WRITELN('(4) Вывести время стоянки;');
      WRITELN('(5) Перенаправить поезда(вывести обычное расписание);');
      WRITELN('(6) Перенаправить поезда(улучшенное расписание);');
      WRITELN('(7) Выход;');
      WRITELN();
      WRITE('Введите номер операции: ');
      READLN(Ch);
      CASE Ch OF 
        '1': PrintTupik(TempTrain);
        '2': BEGIN
              AddTrain(NowTrain, CountS, CountTrain);
              SetLength(ValueDownTime, CountTrain);
              PopCycle(TempTrain);
              PushCopyTupik(NowTrain, TempTrain)
             END;      
        '3': ChangeStopTime(StopTime);
        '4': PrintStopTime(StopTime);
        '5': BEGIN
               CalculationExitTime(StopTime, NowTrain);
               CalculateParkingTime(NowTrain);
               PopCycle(TempTrain);
               PushCopyTupik(NowTrain, TempTrain);
               PrintShedule(TempTrain)
             END;
        '6': BEGIN
               CalculationExitTime(StopTime, NowTrain);
               CalculateParkingTime(NowTrain);
               CalculateDownTime(StopTime, NowTrain);
               WriteValue(ValueDownTime, NowTrain);
               SortValue(ValueDownTime);
               MakeArrayOfMinValue(ValueDownTime, CountS);
               ChangeTypeTrain(NowTrain, ValueDownTime, CountS);
               PopCycle(TempTrain);
               PushCopyTupik(NowTrain, TempTrain);
               PrintShedule(TempTrain);
               CleanTupik(NowTrain, CountS, CountTrain);
               PopCycle(TempTrain)
             END;     
        '7': EXIT
      ELSE
        BEGIN
          WRITELN('Выбрано неккоректное действие');
          WRITELN('Нажмите любую клавишу, чтобы продолжить...');
          READKEY
        END
      END
    END
END.{SheduleTrain}      