abstract public class RankTile extends Tile
{
	protected int rank;
	public RankTile(int rank)
	{
		this.rank = rank;
	}
	public boolean matches(Tile other)
	{
		if(super.matches(other))
		{
				RankTile rt = (RankTile)other;
				if(this.rank == rt.rank)
					return true;
		}
		return false;
	}
}