       identification division.
       program-id. increment.
       data division.
       working-storage section.
       01 i pic 9(9).

       procedure division.
       accept i.
       add 1 to i.
       display i.
       stop run.
