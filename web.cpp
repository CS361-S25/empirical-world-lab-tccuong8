#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "World.h"
#include "Org.h"
#include "Red.h"


emp::web::Document doc{"target"};

class AEAnimator : public emp::web::Animate
{

    // arena width and height
    const int num_h_boxes = 10;
    const int num_w_boxes = 10;
    const double RECT_SIDE = 10;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};

    emp::web::Canvas canvas{width, height, "canvas"};

    emp::Random random{5};
    OrgWorld world{random};

public:
    AEAnimator()
    {
        // shove canvas into the div
        // along with a control button
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");

        emp::Ptr<Organism> org1 = new Red(&random);
        world.Inject(org1);
        // Organism *org2 = new Organism(&random);
        // world.Inject(*org2);

        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);
    }

    

    void DrawOrganism(int x, int y, std::string color)
    {
        int i = x + num_w_boxes * y;
        // Draw the organism at the given x and y coordinates
        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, color, "black");
    }

    void DrawBlank(int x, int y)
    {
        // Draw a blank rectangle at the given x and y coordinates
        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "white", "black");
    }

    void DoFrame() override
    {
        canvas.Clear();
        world.Update();

        int org_num = 0;
        for (int x = 0; x < num_w_boxes; x++)
        {
            for (int y = 0; y < num_h_boxes; y++)
            {
                if (world.IsOccupied(org_num))
                {
                    this->DrawOrganism(x, y, world.GetOrg(org_num)->GetColor());
                }
                else
                {
                    this->DrawBlank(x, y);
                }
                org_num++;
            }
        }
    }
};

AEAnimator animator;

int main() { animator.Step(); }