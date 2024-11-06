program Test;
var
  c: Boolean;

function check(i, j: Integer): Boolean;
begin
  if i <> j then
    begin
      check := False; Exit;
    end;
  check := True;
end;

begin
  writeln('Hello World');
  c := check(1, 2);
  writeln(c);
end.

