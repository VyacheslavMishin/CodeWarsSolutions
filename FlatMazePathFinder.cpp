#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

enum class CellStatus
{
  pathless,
  visited,
  vacant
};

class Cell
{
private:
  CellStatus cell_status;
  int cell_number;
  int cell_x;
  int cell_y;

public:
  Cell();
  Cell(const CellStatus &cell_status, int cell_number, int cell_x, int cell_y);

  CellStatus status() const;
  CellStatus& status();

  int number() const;
  int& number();

  int GetX() const;
  int GetY() const;

};

Cell::Cell()
{

}
Cell::Cell(const CellStatus &cell_status, int cell_number, int cell_x, int cell_y)
{
  this->cell_status = cell_status;
  this->cell_number = cell_number;
  this->cell_x = cell_x;
  this->cell_y = cell_y;
}

CellStatus Cell::status() const
{
  return cell_status;
}

CellStatus& Cell::status()
{
  return cell_status;
}

int Cell::number() const
{
  return cell_number;
}

int& Cell::number()
{
  return cell_number;
}

int Cell::GetX() const
{
  return this->cell_x;
}

int Cell::GetY() const
{
  return this->cell_y;
}

void maze_vectorizor(std::string& maze, std::vector<std::vector<Cell>>& vectorized_maze)
{
  maze.push_back('\n');
  std::vector<Cell> temp_row;

  int current_x_coordinate = 0;

  for (auto symbol : maze)
  {
    if (symbol != '\n')
    {
      if (symbol == '.')
      {
        temp_row.push_back(Cell(CellStatus::vacant, -1, current_x_coordinate, temp_row.size()));
      }
      else if (symbol == 'W')
      {
        temp_row.push_back(Cell(CellStatus::pathless, -1, current_x_coordinate, temp_row.size()));
      }

      continue;
    }

    vectorized_maze.push_back(temp_row);
    temp_row.clear();
    current_x_coordinate ++;
    
  }

  maze.pop_back();

}

int path_finder(std::string maze) 
{ 
  if (maze.front() == 'W' || maze.back() == 'W')
  {
    return -1;
  }

  int x_coord = 0;
  int y_coord = 0;

  std::vector<int> x_steps {1, 0, -1, 0}; // From left to right: down, right, up, left (x_steps and y_steps have to be considered simultaneously)
  std::vector<int> y_steps {0, 1, 0, -1};
   
  std::vector<std::vector<Cell>> vectorized_maze;
  maze_vectorizor(maze, vectorized_maze);

  vectorized_maze.front().front().status() = CellStatus::visited; // initial vertex has been visited
  vectorized_maze.front().front().number() = 0; // counter initialization
  
  std::queue<Cell> wave_front;
  
  wave_front.push(vectorized_maze[0][0]);

  while (wave_front.size() && vectorized_maze.back().back().status() == CellStatus::vacant)
  {
    x_coord = wave_front.front().GetX();
    y_coord = wave_front.front().GetY();
    
    for (size_t i = 0; i < x_steps.size(); i++)
    {
      x_coord += x_steps[i];
      y_coord += y_steps[i];

      if (x_coord >= 0 && y_coord >= 0 && x_coord < vectorized_maze.size() && y_coord < vectorized_maze.front().size())
      {
        if (vectorized_maze[x_coord][y_coord].status() == CellStatus::vacant)
        {
          vectorized_maze[x_coord][y_coord].number() = wave_front.front().number() + 1;
          vectorized_maze[x_coord][y_coord].status() = CellStatus::visited;

          wave_front.push(vectorized_maze[x_coord][y_coord]);  
        }
        
      }

      x_coord -= x_steps[i];
      y_coord -= y_steps[i];
      
      }
    
    wave_front.pop();
  };
  
  return vectorized_maze.back().back().number();
}
