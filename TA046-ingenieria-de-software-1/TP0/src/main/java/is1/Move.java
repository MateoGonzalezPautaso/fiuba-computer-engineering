package is1;

public interface Move {

    Move vs(Move other);

    Move againstRock(Move other);

    Move againstScissors(Move other);

    Move againstPaper(Move other);

}
