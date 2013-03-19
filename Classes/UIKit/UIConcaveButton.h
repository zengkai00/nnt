
# ifndef __WSI_UIKIT_UIPUSHBUTTON_F463DF78399C4B8385D3E996E66F3A1D_H_INCLUDED
# define __WSI_UIKIT_UIPUSHBUTTON_F463DF78399C4B8385D3E996E66F3A1D_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface UIConcaveButton : UIButton {
    
    //! if is pushed.
    BOOL isPushed;
    
    //! image for pushed.
    UIImage *imagePushed;
    UIImage *imageNormal;
    
}

@property (nonatomic) BOOL isPushed;
@property (nonatomic, retain) UIImage *imagePushed, *imageNormal;

- (id)initWithImage:(UIImage*)image;

@end

WSI_END_HEADER_OBJC

# endif