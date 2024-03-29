with Ada.Text_IO, Ada.Integer_Text_IO, Ada.Numerics.Float_Random;
use  Ada.Text_IO, Ada.Integer_Text_IO, Ada.Numerics.Float_Random;

procedure ex8 is

    Count_Failed    : exception;    -- Exception to be raised when counting fails
    Gen             : Generator;    -- Random number generator

    protected type Transaction_Manager (N : Positive) is
    entry Finished;
        entry Wait_Until_Aborted;
        procedure Signal_Abort;
    private
        Finished_Gate_Open  : Boolean := False;
        Aborted             : Boolean := False;
        Aborted_Gate_Open   : Boolean := False;
    end Transaction_Manager;
    protected body Transaction_Manager is
        entry Finished when Finished_Gate_Open or Finished'Count = N is
        begin
            if Finished'Count = N - 1 then
                Finished_Gate_Open := True;
            elsif Finished'Count = 0 then
                Finished_Gate_Open := False;
            end if;
        end Finished;

        entry Wait_Until_Aborted when (Aborted and Wait_Until_Aborted'Count = N) or Aborted_Gate_Open is
        begin
            if Wait_Until_Aborted'Count = N-1 then
                Aborted_Gate_Open := True;
            elsif Wait_Until_Aborted'Count = 0 then
                Aborted_Gate_Open := False;
                Aborted := False;
            end if;
        end Wait_Until_Aborted;

        procedure Signal_Abort is
        begin
            Aborted := True;
        end Signal_Abort;

    end Transaction_Manager;



    
    function Unreliable_Slow_Add (x : Integer) return Integer is
    Error_Rate : Constant := 0.15;  -- (between 0 and 1)
    begin
        -------------------------------------------
        -- PART 1: Create the transaction work here
        -------------------------------------------
        if Random(gen) <= Error_Rate then
            delay Duration(Random(gen)*0.5);
            raise Count_Failed;
        else
            delay Duration(Random(gen)*4.0);
        end if;
        return x + 10;

    end Unreliable_Slow_Add;




    task type Transaction_Worker (Initial : Integer; Manager : access Transaction_Manager);
    task body Transaction_Worker is
        Num         : Integer   := Initial;
        Prev        : Integer   := Num;
        Round_Num   : Integer   := 0;
    begin
        Put_Line ("Worker" & Integer'Image(Initial) & " started");

        loop
            Put_Line ("Worker" & Integer'Image(Initial) & " started round" & Integer'Image(Round_Num));
            Round_Num := Round_Num + 1;

            ---------------------------------------
            -- PART 2: Do the transaction work here             
            ---------------------------------------
            select
                Manager.Wait_Until_Aborted;
                Num := Prev + 5;

            then abort
                begin
                    Num := Unreliable_Slow_Add(num);
                exception
                    when Count_Failed =>
                        Manager.Signal_Abort;
                end;
                Manager.Finished;
            end select;
            
            

            Put_Line ("  Worker" & Integer'Image(Initial) & " comitting" & Integer'Image(Num));
                -------------------------------------------
                -- PART 2: Roll back to previous value here
                -------------------------------------------

            Prev := Num;
            delay 0.5;

        end loop;
    end Transaction_Worker;

    Manager : aliased Transaction_Manager (3);

    Worker_1 : Transaction_Worker (0, Manager'Access);
    Worker_2 : Transaction_Worker (1, Manager'Access);
    Worker_3 : Transaction_Worker (2, Manager'Access);

begin
    Reset(Gen); -- Seed the random number generator
end ex8;