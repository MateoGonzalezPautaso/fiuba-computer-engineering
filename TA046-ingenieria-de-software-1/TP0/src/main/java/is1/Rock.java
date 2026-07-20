package is1;

public class Rock implements Move {

    public Move vs(Move other) {
        return other.againstRock(this);
    }

    public Move againstRock(Move other) {
        return this;
    }

    public Move againstPaper(Move other) { return other; }

    public Move againstScissors(Move other) {
        return this;
    }

}
