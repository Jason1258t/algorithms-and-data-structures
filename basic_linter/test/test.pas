program Nested;

begin
    repeat
        case i of
            1: begin
                   writeln('Case 1');
               end;
            2: begin
                   writeln('Case 2');
               end;
        end;
    until i = 0;

    record
        name: string;
        age: integer;
    end;

    writeln('Done');
end1.
end;