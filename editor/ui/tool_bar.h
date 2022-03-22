//  Copyright (c) 2022 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#ifndef tool_bar_hpp
#define tool_bar_hpp

#include "ui/widgets/buttons/button_image.h"
#include "ui/widgets/panel_transformables/panel_window.h"

namespace vox {
using namespace ui;

namespace editor {
namespace ui {
class Toolbar : public PanelWindow {
public:
    /**
     * Constructor
     * @param p_title p_title
     * @param p_opened p_opened
     * @param p_windowSettings p_windowSettings
     */
    Toolbar(const std::string &p_title,
            bool p_opened,
            const PanelWindowSettings &p_windowSettings);
    
    /**
     * Custom implementation of the draw method
     */
    void _draw_Impl() override;
    
private:
    ButtonImage *m_playButton;
    ButtonImage *m_pauseButton;
    ButtonImage *m_stopButton;
    ButtonImage *m_nextButton;
};

}
}
}
#endif /* tool_bar_hpp */